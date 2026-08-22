object frmEditBounds: TfrmEditBounds
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Edit Fractal Bounds'
  ClientHeight = 202
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
    Left = 7
    Top = 16
    Width = 353
    Height = 153
    Shape = bsFrame
  end
  object Label5: TLabel
    Left = 32
    Top = 34
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
    Top = 42
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
    Top = 61
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
    Top = 69
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
    Top = 88
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
    Top = 96
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
    Top = 115
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
    Top = 123
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
    Left = 204
    Top = 175
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = bOKClick
  end
  object bCancel: TBitBtn
    Left = 285
    Top = 175
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object eXMin: TEdit
    Left = 80
    Top = 37
    Width = 145
    Height = 21
    Alignment = taRightJustify
    TabOrder = 2
    Text = '0'
  end
  object eXMax: TEdit
    Left = 80
    Top = 64
    Width = 145
    Height = 21
    Alignment = taRightJustify
    TabOrder = 3
    Text = '0'
  end
  object eYMin: TEdit
    Left = 80
    Top = 91
    Width = 145
    Height = 21
    Alignment = taRightJustify
    TabOrder = 4
    Text = '0'
  end
  object eYMax: TEdit
    Left = 80
    Top = 118
    Width = 145
    Height = 21
    Alignment = taRightJustify
    TabOrder = 5
    Text = '0'
  end
  object rbNoFitting: TRadioButton
    Left = 256
    Top = 42
    Width = 65
    Height = 17
    Caption = 'No fitting'
    Checked = True
    TabOrder = 6
    TabStop = True
  end
  object rbAutoFitting: TRadioButton
    Left = 256
    Top = 65
    Width = 89
    Height = 17
    Caption = 'Auto fitting'
    TabOrder = 7
  end
end
