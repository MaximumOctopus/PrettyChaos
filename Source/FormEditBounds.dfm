object frmEditBounds: TfrmEditBounds
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Edit Fractal Bounds'
  ClientHeight = 195
  ClientWidth = 368
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poMainFormCenter
  OnShow = FormShow
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 353
    Height = 153
    Shape = bsFrame
  end
  object Label5: TLabel
    Left = 32
    Top = 26
    Width = 7
    Height = 13
    Caption = 'X'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 40
    Top = 34
    Width = 15
    Height = 11
    Caption = 'Min'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 32
    Top = 53
    Width = 7
    Height = 13
    Caption = 'X'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 40
    Top = 61
    Width = 17
    Height = 11
    Caption = 'Max'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 32
    Top = 80
    Width = 7
    Height = 13
    Caption = 'Y'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 40
    Top = 88
    Width = 15
    Height = 11
    Caption = 'Min'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 32
    Top = 107
    Width = 7
    Height = 13
    Caption = 'Y'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 40
    Top = 115
    Width = 17
    Height = 11
    Caption = 'Max'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -9
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object bOK: TBitBtn
    Left = 205
    Top = 167
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
    OnClick = bOKClick
  end
  object bCancel: TBitBtn
    Left = 286
    Top = 167
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object eXMin: TEdit
    Left = 80
    Top = 29
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'eXMin'
  end
  object eXMax: TEdit
    Left = 80
    Top = 56
    Width = 121
    Height = 21
    TabOrder = 3
    Text = 'Edit1'
  end
  object eYMin: TEdit
    Left = 80
    Top = 83
    Width = 121
    Height = 21
    TabOrder = 4
    Text = 'Edit1'
  end
  object eYMax: TEdit
    Left = 80
    Top = 110
    Width = 121
    Height = 21
    TabOrder = 5
    Text = 'Edit1'
  end
  object rbNoFitting: TRadioButton
    Left = 256
    Top = 34
    Width = 65
    Height = 17
    Caption = 'No fitting'
    Checked = True
    TabOrder = 6
    TabStop = True
  end
  object rbAutoFitting: TRadioButton
    Left = 256
    Top = 57
    Width = 89
    Height = 17
    Caption = 'Auto fitting'
    TabOrder = 7
  end
end
