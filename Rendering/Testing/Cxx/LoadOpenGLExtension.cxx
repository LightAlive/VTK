// -*- c++ -*-

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    LoadOpenGLExtension.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

/*
 * Copyright 2004 Sandia Corporation.
 * Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 * license for use of this work by or on behalf of the
 * U.S. Government. Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that this Notice and any
 * statement of authorship are reproduced on all copies.
 */

// This code test to make sure vtkOpenGLExtensionManager can properly get
// extension functions that can be used.  To do this, we convolve an image
// with a kernel for a Laplacian filter.  This requires the use of functions
// defined in OpenGL 1.2, which should be available pretty much everywhere
// but still has functions that can be loaded as extensions.

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkCallbackCommand.h"
#include "vtkUnsignedCharArray.h"
#include "vtkRegressionTestImage.h"
#include "vtkOpenGLExtensionManager.h"
#include "vtkgl.h"

vtkUnsignedCharArray *image;

GLfloat laplacian[3][3] = {
  { -0.125f, -0.125f, -0.125f },
  { -0.125f,  1.0f,   -0.125f },
  { -0.125f, -0.125f, -0.125f }
};

static void ImageCallback(vtkObject *__renwin, unsigned long, void *, void *)
{
  vtkRenderWindow *renwin = static_cast<vtkRenderWindow *>(__renwin);
  int *size = renwin->GetSize();

  // Turn on convolution filtering for when we read the image.
  glEnable(vtkgl::CONVOLUTION_2D);

  renwin->GetRGBACharPixelData(0, 0, size[0]-1, size[1]-1, 0, image);

  // Now turn it off for writing back out.
  glDisable(vtkgl::CONVOLUTION_2D);

  renwin->SetRGBACharPixelData(0, 0, size[0]-1, size[1]-1, image, 0);

  renwin->SwapBuffersOn();
  renwin->Frame();
  renwin->SwapBuffersOff();
}

int LoadOpenGLExtension(int argc, char *argv[])
{
  vtkRenderWindow *renwin = vtkRenderWindow::New();
  renwin->SetSize(250, 250);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  renwin->SetInteractor(iren);

  vtkOpenGLExtensionManager *extensions = vtkOpenGLExtensionManager::New();
  extensions->SetRenderWindow(renwin);

  if (!extensions->ExtensionSupported("GL_VERSION_1_2"))
    {
    cerr << "Is it possible that your driver does not support OpenGL 1.2?\n";
    cout << "Some drivers report supporting only GL 1.1 even though they\n"
         << "actually support 1.2 (and probably higher).  I'm going to\n"
         << "try to load the extension anyway.  You will definitely get\n"
         << "a warning from vtkOpenGLExtensionManager about it.  If GL 1.2\n"
         << "really is not supported (or something else is wrong), I will\n"
         << "seg fault.\n\n";
    }
  extensions->LoadExtension("GL_VERSION_1_2");
  extensions->Delete();

  vtkConeSource *cone = vtkConeSource::New();

  vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
  mapper->SetInput(cone->GetOutput());

  vtkActor *actor = vtkActor::New();
  actor->SetMapper(mapper);

  vtkRenderer *renderer = vtkRenderer::New();
  renderer->AddActor(actor);

  renwin->AddRenderer(renderer);

  vtkCamera *camera = renderer->GetActiveCamera();
  camera->Elevation(-45);

  // Do a render without convolution filter.
  renwin->Render();

  // Set up a convolution filter.  We are using the Laplacian filter, which
  // is basically an edge detector.  Once vtkgl::CONVOLUTION_2D is enabled,
  // the filter will be applied any time an image is transfered in the
  // pipeline.
  vtkgl::ConvolutionFilter2D(vtkgl::CONVOLUTION_2D, GL_LUMINANCE, 3, 3,
                             GL_LUMINANCE, GL_FLOAT, laplacian);
  vtkgl::ConvolutionParameteri(vtkgl::CONVOLUTION_2D,
                               vtkgl::CONVOLUTION_BORDER_MODE,
                               vtkgl::REPLICATE_BORDER);

  image = vtkUnsignedCharArray::New();
  vtkCallbackCommand *cbc = vtkCallbackCommand::New();
  cbc->SetCallback(ImageCallback);
  renwin->AddObserver(vtkCommand::EndEvent, cbc);
  cbc->Delete();

  // This is a bit of a hack.  The EndEvent on the render window will swap
  // the buffers.
  renwin->SwapBuffersOff();

  int retVal = vtkRegressionTestImage(renwin);
  if (retVal == vtkRegressionTester::DO_INTERACTOR)
    {
    iren->Start();
    }

  cone->Delete();
  mapper->Delete();
  actor->Delete();
  renderer->Delete();
  renwin->Delete();
  iren->Delete();
  image->Delete();

  return !retVal;
}
