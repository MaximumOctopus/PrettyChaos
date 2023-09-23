object frmColourDialog: TfrmColourDialog
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Colour Select'
  ClientHeight = 198
  ClientWidth = 562
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object sShapeColour: TShape
    Left = 8
    Top = 8
    Width = 145
    Height = 129
  end
  object Bevel1: TBevel
    Left = 8
    Top = 152
    Width = 545
    Height = 5
    Shape = bsTopLine
  end
  object Label1: TLabel
    Left = 170
    Top = 24
    Width = 7
    Height = 13
    Caption = 'R'
  end
  object Label2: TLabel
    Left = 170
    Top = 63
    Width = 7
    Height = 13
    Caption = 'G'
  end
  object Label3: TLabel
    Left = 170
    Top = 102
    Width = 6
    Height = 13
    Caption = 'B'
  end
  object lRValue: TLabel
    Left = 519
    Top = 24
    Width = 7
    Height = 13
    Caption = 'R'
  end
  object lGValue: TLabel
    Left = 519
    Top = 63
    Width = 7
    Height = 13
    Caption = 'G'
  end
  object lBValue: TLabel
    Left = 519
    Top = 102
    Width = 6
    Height = 13
    Caption = 'B'
  end
  object tbRed: TTrackBar
    Left = 192
    Top = 24
    Width = 321
    Height = 33
    Max = 255
    TabOrder = 0
    OnChange = tbRedChange
  end
  object tbGreen: TTrackBar
    Left = 192
    Top = 63
    Width = 321
    Height = 33
    Max = 255
    TabOrder = 1
    OnChange = tbRedChange
  end
  object tbBlue: TTrackBar
    Left = 192
    Top = 102
    Width = 321
    Height = 33
    Max = 255
    TabOrder = 2
    OnChange = tbRedChange
  end
  object BitBtn1: TBitBtn
    Left = 397
    Top = 165
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 3
  end
  object BitBtn2: TBitBtn
    Left = 478
    Top = 165
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 4
  end
end
