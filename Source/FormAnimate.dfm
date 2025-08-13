object frmAnimate: TfrmAnimate
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Animate'
  ClientHeight = 350
  ClientWidth = 472
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
    Left = 8
    Top = 8
    Width = 457
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
    Top = 264
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
  object Label4: TLabel
    Left = 24
    Top = 190
    Width = 65
    Height = 15
    Caption = 'Parameter D'
  end
  object lWarning: TLabel
    Left = 24
    Top = 308
    Width = 231
    Height = 15
    Caption = 'Error with settings or no animate source set!'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object Label5: TLabel
    Left = 24
    Top = 219
    Width = 63
    Height = 15
    Caption = 'Parameter E'
  end
  object eDeltaA: TEdit
    Left = 112
    Top = 100
    Width = 80
    Height = 23
    Alignment = taRightJustify
    TabOrder = 0
    Text = '0'
    OnChange = eDeltaAChange
  end
  object eDeltaB: TEdit
    Left = 112
    Top = 129
    Width = 80
    Height = 23
    Alignment = taRightJustify
    TabOrder = 1
    Text = '0'
    OnChange = eDeltaAChange
  end
  object eDeltaC: TEdit
    Left = 112
    Top = 158
    Width = 80
    Height = 23
    Alignment = taRightJustify
    TabOrder = 2
    Text = '0'
    OnChange = eDeltaAChange
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
    Top = 261
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
  object eDeltaD: TEdit
    Left = 112
    Top = 187
    Width = 80
    Height = 23
    Alignment = taRightJustify
    TabOrder = 9
    Text = '0'
    OnChange = eDeltaAChange
  end
  object cbIncludeA: TCheckBox
    Left = 198
    Top = 103
    Width = 123
    Height = 17
    Caption = 'include in filename'
    TabOrder = 10
  end
  object cbIncludeB: TCheckBox
    Left = 198
    Top = 132
    Width = 123
    Height = 17
    Caption = 'include in filename'
    TabOrder = 11
  end
  object cbIncludeC: TCheckBox
    Left = 198
    Top = 161
    Width = 123
    Height = 17
    Caption = 'include in filename'
    TabOrder = 12
  end
  object cbIncludeD: TCheckBox
    Left = 198
    Top = 190
    Width = 123
    Height = 17
    Caption = 'include in filename'
    TabOrder = 13
  end
  object cbIncludeE: TCheckBox
    Left = 198
    Top = 219
    Width = 123
    Height = 17
    Caption = 'include in filename'
    TabOrder = 14
  end
  object eDeltaE: TEdit
    Left = 112
    Top = 216
    Width = 80
    Height = 23
    Alignment = taRightJustify
    TabOrder = 15
    Text = '0'
    OnChange = eDeltaAChange
  end
end
