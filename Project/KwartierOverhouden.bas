Attribute VB_Name = "Module1"

Public Sub KwartierOverhouden()

Dim i, LastRow As Long
Dim inh As String

With ActiveSheet
    LastRow = .Cells(.Rows.Count, "A").End(xlUp).Row
End With

For i = 2 To LastRow
    inh = Range("A" & i).Value
    If (Not inh Like "*:00") And (Not inh Like "*:15") And (Not inh Like "*:30") And (Not inh Like "*:45") Then
        Rows(i).EntireRow.Delete
    End If
Next

MsgBox ("Done")

End Sub
