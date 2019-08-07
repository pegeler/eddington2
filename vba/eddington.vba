Option Explicit
Function Eddington_number(rides As Range) As Integer
' Calculates the Eddington number for cycling
' Use in Microsoft Excel
  
  Eddington_number = 0
  
  With CreateObject("System.Collections.ArrayList")

    Dim cell As Range
    For Each cell In rides.Cells
      If IsEmpty(cell) = False Then .Add CInt(cell.Value2)
    Next cell

    .Sort
    .Reverse
  
    Dim ride As Variant
    For Each ride In .toarray
      If ride < Eddington_number + 1 Then Exit Function
      Eddington_number = Eddington_number + 1
    Next ride
  
  End With
End Function
