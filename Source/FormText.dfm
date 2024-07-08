object frmText: TfrmText
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Image Text Description'
  ClientHeight = 263
  ClientWidth = 358
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poOwnerFormCenter
  TextHeight = 15
  object Label1: TLabel
    Left = 40
    Top = 96
    Width = 51
    Height = 15
    Caption = 'Font Size'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 40
    Top = 75
    Width = 61
    Height = 15
    Caption = 'Font Name'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lFontName: TLabel
    Left = 120
    Top = 75
    Width = 9
    Height = 15
    Caption = '...'
  end
  object lFontSize: TLabel
    Left = 120
    Top = 96
    Width = 9
    Height = 15
    Caption = '...'
  end
  object Label3: TLabel
    Left = 40
    Top = 179
    Width = 46
    Height = 15
    Caption = 'Y-offset'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object cbEnable: TCheckBox
    Left = 16
    Top = 24
    Width = 217
    Height = 17
    Caption = 'Add description to rendered image'
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 40
    Top = 117
    Width = 75
    Height = 25
    Caption = 'Font'
    TabOrder = 1
    OnClick = BitBtn1Click
  end
  object bCancel: TBitBtn
    Left = 275
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Close'
    ModalResult = 2
    TabOrder = 2
  end
  object bOK: TBitBtn
    Left = 194
    Top = 232
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 3
  end
  object eYOffset: TEdit
    Left = 120
    Top = 176
    Width = 57
    Height = 23
    Alignment = taRightJustify
    TabOrder = 4
    Text = '0'
  end
  object fdText: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Left = 304
    Top = 16
  end
end
