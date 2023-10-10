object frmAnimate: TfrmAnimate
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Animate'
  ClientHeight = 344
  ClientWidth = 468
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poMainFormCenter
  OnShow = FormShow
  TextHeight = 15
  object Bevel1: TBevel
    Left = 0
    Top = 8
    Width = 465
    Height = 333
  end
  object lVariableA: TLabel
    Left = 24
    Top = 103
    Width = 65
    Height = 15
    Caption = 'Parameter A'
  end
  object lVariableB: TLabel
    Left = 24
    Top = 132
    Width = 64
    Height = 15
    Caption = 'Parameter B'
  end
  object lVariableC: TLabel
    Left = 24
    Top = 161
    Width = 65
    Height = 15
    Caption = 'Parameter C'
  end
  object Label1: TLabel
    Left = 24
    Top = 32
    Width = 28
    Height = 15
    Caption = 'Steps'
  end
  object Label2: TLabel
    Left = 24
    Top = 224
    Width = 66
    Height = 15
    Caption = 'Image Prefix'
  end
  object Label3: TLabel
    Left = 112
    Top = 79
    Width = 59
    Height = 15
    Caption = 'delta / step'
  end
  object eDeltaA: TEdit
    Left = 112
    Top = 100
    Width = 80
    Height = 23
    Alignment = taRightJustify
    TabOrder = 0
    Text = '0'
  end
  object eDeltaB: TEdit
    Left = 112
    Top = 129
    Width = 80
    Height = 23
    Alignment = taRightJustify
    TabOrder = 1
    Text = '0'
  end
  object eDeltaC: TEdit
    Left = 112
    Top = 158
    Width = 80
    Height = 23
    Alignment = taRightJustify
    TabOrder = 2
    Text = '0'
  end
  object eSteps: TEdit
    Left = 112
    Top = 29
    Width = 41
    Height = 23
    Alignment = taRightJustify
    NumbersOnly = True
    TabOrder = 3
    Text = '10'
  end
  object bOK: TBitBtn
    Left = 296
    Top = 304
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 4
    OnClick = bOKClick
  end
  object bCancel: TBitBtn
    Left = 377
    Top = 304
    Width = 75
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
  end
  object ePrefix: TEdit
    Left = 112
    Top = 221
    Width = 228
    Height = 23
    TabOrder = 6
    Text = '$yyyy$mm$dd_$Th$Tm$Ts_'
  end
  object cbAnimateParameters: TCheckBox
    Left = 256
    Top = 32
    Width = 145
    Height = 17
    Caption = 'Animate  parameters'
    TabOrder = 7
  end
  object cbAnimateZoom: TCheckBox
    Left = 256
    Top = 55
    Width = 145
    Height = 17
    Caption = 'Animate  zoom'
    TabOrder = 8
  end
end
