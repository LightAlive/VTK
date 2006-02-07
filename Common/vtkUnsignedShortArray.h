/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkUnsignedShortArray.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkUnsignedShortArray - dynamic, self-adjusting array of unsigned short
// .SECTION Description
// vtkUnsignedShortArray is an array of values of type unsigned short.
// It provides methods for insertion and retrieval of values and will
// automatically resize itself to hold new data.

#ifndef __vtkUnsignedShortArray_h
#define __vtkUnsignedShortArray_h

// Tell the template header how to give our superclass a DLL interface.
#if !defined(__vtkUnsignedShortArray_cxx)
# define VTK_DATA_ARRAY_TEMPLATE_TYPE unsigned short
#endif

#include "vtkDataArray.h"
#include "vtkDataArrayTemplate.h" // Real Superclass

// Fake the superclass for the wrappers.
#define vtkDataArray vtkDataArrayTemplate<unsigned short>
class VTK_COMMON_EXPORT vtkUnsignedShortArray : public vtkDataArray
#undef vtkDataArray
{
public:
  static vtkUnsignedShortArray* New();
  vtkTypeRevisionMacro(vtkUnsignedShortArray,vtkDataArray);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the data type.
  int GetDataType()
    { return VTK_UNSIGNED_SHORT; }

  // Description:
  // Copy the tuple value into a user-provided array.
  void GetTupleValue(vtkIdType i, unsigned short* tuple)
    { this->RealSuperclass::GetTupleValue(i, tuple); }

  // Description:
  // Set the tuple value at the ith location in the array.
  void SetTupleValue(vtkIdType i, const unsigned short* tuple)
    { this->RealSuperclass::SetTupleValue(i, tuple); }

  // Description:
  // Insert (memory allocation performed) the tuple into the ith location
  // in the array.
  void InsertTupleValue(vtkIdType i, const unsigned short* tuple)
    { this->RealSuperclass::InsertTupleValue(i, tuple); }

  // Description:
  // Insert (memory allocation performed) the tuple onto the end of the array.
  vtkIdType InsertNextTupleValue(const unsigned short* tuple)
    { return this->RealSuperclass::InsertNextTupleValue(tuple); }

  // Description:
  // Get the data at a particular index.
  unsigned short GetValue(vtkIdType id)
    { return this->RealSuperclass::GetValue(id); }

  // Description:
  // Set the data at a particular index. Does not do range checking. Make sure
  // you use the method SetNumberOfValues() before inserting data.
  void SetValue(vtkIdType id, unsigned short value)
    { this->RealSuperclass::SetValue(id, value); }

  // Description:
  // Specify the number of values for this object to hold. Does an
  // allocation as well as setting the MaxId ivar. Used in conjunction with
  // SetValue() method for fast insertion.
  void SetNumberOfValues(vtkIdType number)
    { this->RealSuperclass::SetNumberOfValues(number); }

  // Description:
  // Insert data at a specified position in the array.
  void InsertValue(vtkIdType id, unsigned short f)
    { this->RealSuperclass::InsertValue(id, f); }

  // Description:
  // Insert data at the end of the array. Return its location in the array.
  vtkIdType InsertNextValue(unsigned short f)
    { return this->RealSuperclass::InsertNextValue(f); }

  // Description:
  // Get the address of a particular data index. Make sure data is allocated
  // for the number of items requested. Set MaxId according to the number of
  // data values requested.
  unsigned short* WritePointer(vtkIdType id, vtkIdType number)
    { return this->RealSuperclass::WritePointer(id, number); }

  // Description:
  // Get the address of a particular data index. Performs no checks
  // to verify that the memory has been allocated etc.
  unsigned short* GetPointer(vtkIdType id)
    { return this->RealSuperclass::GetPointer(id); }

  // Description:
  // This method lets the user specify data to be held by the array.  The
  // array argument is a pointer to the data.  size is the size of
  // the array supplied by the user.  Set save to 1 to keep the class
  // from deleting the array when it cleans up or reallocates memory.
  // The class uses the actual array provided; it does not copy the data
  // from the suppled array. If save is 0, then this class is free to delete
  // the array when it cleans up or reallocates. In that case, it is required 
  // that the array was allocated using the C++ new operator (and not malloc).
  void SetArray(unsigned short* array, vtkIdType size, int save)
    { this->RealSuperclass::SetArray(array, size, save); }

protected:
  vtkUnsignedShortArray(vtkIdType numComp=1);
  ~vtkUnsignedShortArray();

private:
  //BTX
  typedef vtkDataArrayTemplate<unsigned short> RealSuperclass;
  //ETX
  vtkUnsignedShortArray(const vtkUnsignedShortArray&);  // Not implemented.
  void operator=(const vtkUnsignedShortArray&);  // Not implemented.
};

#endif
