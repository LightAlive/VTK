/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkImageGradientMagnitude.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkImageGradientMagnitude - Computes magnitude of the gradient.

// .SECTION Description
// vtkImageGradientMagnitude computes the gradient magnitude of an image.
// Setting the dimensionality determines whether the gradient is computed on
// 2D images, or 3D volumes.  The default is two dimensional XY images.

// .SECTION See Also
// vtkImageGradient vtkImageMagnitude

#ifndef __vtkImageGradientMagnitude_h
#define __vtkImageGradientMagnitude_h


#include "vtkThreadedImageAlgorithm.h"

class VTK_IMAGING_EXPORT vtkImageGradientMagnitude : public vtkThreadedImageAlgorithm
{
public:
  static vtkImageGradientMagnitude *New();
  vtkTypeRevisionMacro(vtkImageGradientMagnitude,vtkThreadedImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // If "HandleBoundariesOn" then boundary pixels are duplicated
  // So central differences can get values.
  vtkSetMacro(HandleBoundaries, int);
  vtkGetMacro(HandleBoundaries, int);
  vtkBooleanMacro(HandleBoundaries, int);

  // Description:
  // Determines how the input is interpreted (set of 2d slices ...)
  vtkSetClampMacro(Dimensionality,int,2,3);
  vtkGetMacro(Dimensionality,int);
  
  // Description:
  // If you want to compute the gradient magnitude of an arbitrary point 
  // scalar array, then set its name here.
  // By default this in NULL and the filter will use the active scalar array.
  vtkGetStringMacro(InputScalarsSelection);
  void SelectInputScalars(const char *fieldName) 
    {this->SetInputScalarsSelection(fieldName);}  

protected:
  vtkImageGradientMagnitude();
  ~vtkImageGradientMagnitude() {};

  int HandleBoundaries;
  int Dimensionality;
  
  void ExecuteInformation (vtkInformation *, vtkInformationVector *, vtkInformationVector *);
  void ComputeInputUpdateExtent (vtkInformation *, vtkInformationVector *, vtkInformationVector *);
  
  void ThreadedExecute (vtkImageData ***inData, vtkImageData **outData,
                       int extent[6], int id);
private:
  vtkImageGradientMagnitude(const vtkImageGradientMagnitude&);  // Not implemented.
  void operator=(const vtkImageGradientMagnitude&);  // Not implemented.
};

#endif



