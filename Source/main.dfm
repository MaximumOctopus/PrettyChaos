object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'PrettyChaos'
  ClientHeight = 1114
  ClientWidth = 1584
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  Position = poMainFormCenter
  ShowHint = True
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1584
    Height = 34
    Align = alTop
    TabOrder = 0
    object sbRender: TSpeedButton
      Left = 311
      Top = 2
      Width = 89
      Height = 27
      Caption = 'Render'
      OnClick = sbRenderClick
    end
    object sbSaveImage: TSpeedButton
      Left = 207
      Top = 2
      Width = 89
      Height = 27
      Caption = 'Export'
      ImageIndex = 5
      Images = ImageList1
      OnClick = sbSaveImageClick
    end
    object bSaveProject: TSpeedButton
      Left = 102
      Top = 2
      Width = 89
      Height = 27
      Caption = 'Save'
      ImageIndex = 6
      Images = ImageList1
      OnClick = bSaveProjectClick
    end
    object bOpenProject: TSpeedButton
      Left = 7
      Top = 2
      Width = 89
      Height = 27
      Caption = 'Open'
      ImageIndex = 7
      Images = ImageList1
      OnClick = bOpenProjectClick
    end
    object Bevel2: TBevel
      Left = 198
      Top = 2
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
    object Bevel3: TBevel
      Left = 302
      Top = 2
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
    object sbReset: TSpeedButton
      Left = 509
      Top = 2
      Width = 30
      Height = 27
      Hint = 'reset zoom'
      ImageIndex = 1
      Images = ImageList1
      OnClick = sbResetClick
    end
    object sbZoom: TSpeedButton
      Left = 617
      Top = 1
      Width = 30
      Height = 27
      Hint = 'zoom in'
      ImageIndex = 0
      Images = ImageList1
      OnClick = sbZoomClick
    end
    object sbZoomCrop: TSpeedButton
      Left = 744
      Top = 2
      Width = 30
      Height = 27
      Hint = 'zoom to region'
      ImageIndex = 8
      Images = ImageList1
      OnClick = sbZoomCropClick
    end
    object sbBack: TSpeedButton
      Left = 780
      Top = 2
      Width = 30
      Height = 27
      Hint = 'previous zoom view'
      ImageIndex = 2
      Images = ImageList1
      OnClick = sbBackClick
    end
    object sbForward: TSpeedButton
      Left = 818
      Top = 2
      Width = 30
      Height = 27
      Hint = 'next zoom view'
      ImageIndex = 3
      Images = ImageList1
      OnClick = sbBackClick
    end
    object Bevel4: TBevel
      Left = 501
      Top = 2
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
    object Bevel5: TBevel
      Left = 854
      Top = 4
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
    object sbAbout: TSpeedButton
      Left = 1069
      Top = 4
      Width = 30
      Height = 27
      Hint = 'about'
      ImageIndex = 11
      Images = ImageList1
      OnClick = sbAboutClick
    end
    object eAnimation: TSpeedButton
      Left = 406
      Top = 1
      Width = 89
      Height = 27
      Caption = 'Animation'
      Enabled = False
      OnClick = eAnimationClick
    end
    object sbReZoom: TSpeedButton
      Left = 653
      Top = 1
      Width = 30
      Height = 27
      Hint = 'repeat last zoom'
      ImageIndex = 10
      Images = ImageList1
      Enabled = False
      OnClick = sbReZoomClick
    end
    object sbResetAll: TSpeedButton
      Left = 862
      Top = 4
      Width = 30
      Height = 27
      Hint = 'reset all parameters'
      ImageIndex = 12
      Images = ImageList1
      OnClick = sbResetAllClick
    end
    object Bevel6: TBevel
      Left = 899
      Top = 4
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
    object sbZoomOnPoint: TSpeedButton
      Left = 545
      Top = 1
      Width = 30
      Height = 27
      Hint = 'centre image on a point (no zoom)'
      ImageIndex = 13
      Images = ImageList1
      OnClick = sbZoomOnPointClick
    end
    object sbCopyImage: TSpeedButton
      Left = 907
      Top = 4
      Width = 30
      Height = 27
      Hint = 'copy image to buffer'
      ImageIndex = 14
      Images = ImageList1
      OnClick = sbCopyImageClick
    end
    object sbMergeImage: TSpeedButton
      Left = 943
      Top = 4
      Width = 30
      Height = 27
      Hint = 'merge render with buffer'
      ImageIndex = 15
      Images = ImageList1
      OnClick = sbMergeImageClick
    end
    object Bevel7: TBevel
      Left = 1016
      Top = 4
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
    object sbSwapImage: TSpeedButton
      Left = 979
      Top = 4
      Width = 30
      Height = 27
      Hint = 'swap between render and backup'
      ImageIndex = 16
      Images = ImageList1
      OnClick = sbSwapImageClick
    end
    object sbDescription: TSpeedButton
      Left = 1024
      Top = 4
      Width = 30
      Height = 27
      Hint = 'edit on-image text parameters'
      ImageIndex = 17
      Images = ImageList1
      OnClick = sbDescriptionClick
    end
    object Bevel8: TBevel
      Left = 1062
      Top = 3
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
    object sbZoomCentre: TSpeedButton
      Left = 581
      Top = 1
      Width = 30
      Height = 27
      Hint = 'zoom at image centre'
      ImageIndex = 18
      Images = ImageList1
      OnClick = sbZoomCentreClick
    end
    object sbZoomOut: TSpeedButton
      Left = 699
      Top = 2
      Width = 30
      Height = 27
      Hint = 'zoom out'
      ImageIndex = 19
      Images = ImageList1
      OnClick = sbZoomOutClick
    end
    object Bevel9: TBevel
      Left = 691
      Top = 2
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
    object Bevel10: TBevel
      Left = 736
      Top = 2
      Width = 6
      Height = 28
      Shape = bsLeftLine
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 34
    Width = 1584
    Height = 1061
    Align = alClient
    TabOrder = 1
    OnMouseMove = Panel3MouseMove
    ExplicitHeight = 1038
    object iRender: TImage
      Left = 0
      Top = 1
      Width = 1280
      Height = 1024
      OnMouseDown = iRenderMouseDown
      OnMouseMove = iRenderMouseMove
    end
    object pMain: TPanel
      Left = 1352
      Top = 1
      Width = 231
      Height = 1059
      Align = alRight
      Color = clWhite
      ParentBackground = False
      TabOrder = 0
      ExplicitHeight = 1036
      object PageControl1: TPageControl
        Left = 1
        Top = 1
        Width = 229
        Height = 808
        ActivePage = TabSheet1
        Align = alClient
        TabOrder = 0
        ExplicitHeight = 786
        object TabSheet1: TTabSheet
          Caption = 'Fractal'
          object Label16: TLabel
            Left = 14
            Top = 7
            Width = 33
            Height = 13
            Caption = 'Fractal'
          end
          object Bevel1: TBevel
            Left = 3
            Top = 38
            Width = 215
            Height = 10
            Shape = bsTopLine
          end
          object GroupBox4: TGroupBox
            Left = 3
            Top = 685
            Width = 212
            Height = 87
            Caption = 'Cursor'
            DoubleBuffered = True
            ParentDoubleBuffered = False
            TabOrder = 0
            object lCursor: TLabel
              Left = 15
              Top = 27
              Width = 146
              Height = 13
              AutoSize = False
              Caption = '...'
            end
            object lCursorColour: TLabel
              Left = 15
              Top = 65
              Width = 146
              Height = 13
              AutoSize = False
              Caption = '...'
            end
            object lCursorAbsolute: TLabel
              Left = 15
              Top = 46
              Width = 146
              Height = 13
              AutoSize = False
              Caption = '...'
            end
          end
          object GroupBox2: TGroupBox
            Left = 3
            Top = 505
            Width = 212
            Height = 174
            Caption = 'Dimensions'
            TabOrder = 1
            object lXMin: TLabel
              Left = 72
              Top = 56
              Width = 130
              Height = 13
              AutoSize = False
              Caption = 'lXMin'
            end
            object lXMax: TLabel
              Left = 72
              Top = 75
              Width = 130
              Height = 13
              AutoSize = False
              Caption = 'Label1'
            end
            object lYMin: TLabel
              Left = 72
              Top = 94
              Width = 130
              Height = 13
              AutoSize = False
              Caption = 'Label1'
            end
            object lYMax: TLabel
              Left = 72
              Top = 113
              Width = 130
              Height = 13
              AutoSize = False
              Caption = 'Label1'
            end
            object Label4: TLabel
              Left = 24
              Top = 121
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
            object Label8: TLabel
              Left = 16
              Top = 113
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
            object Label7: TLabel
              Left = 16
              Top = 94
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
              Left = 24
              Top = 102
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
            object Label2: TLabel
              Left = 24
              Top = 83
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
            object Label6: TLabel
              Left = 16
              Top = 75
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
            object Label5: TLabel
              Left = 16
              Top = 56
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
              Left = 24
              Top = 64
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
            object lWidth: TLabel
              Left = 16
              Top = 27
              Width = 19
              Height = 13
              Caption = 'Size'
            end
            object Label9: TLabel
              Left = 118
              Top = 27
              Width = 6
              Height = 13
              Caption = 'x'
            end
            object sbCopyBoundsToClipboard: TSpeedButton
              Left = 45
              Top = 142
              Width = 23
              Height = 22
              ImageIndex = 9
              Images = ImageList1
              OnClick = sbCopyBoundsToClipboardClick
            end
            object sbEditBounds: TSpeedButton
              Left = 16
              Top = 142
              Width = 23
              Height = 22
              ImageIndex = 4
              Images = ImageList1
              OnClick = sbEditBoundsClick
            end
            object eWidth: TEdit
              Left = 65
              Top = 24
              Width = 45
              Height = 21
              Alignment = taRightJustify
              NumbersOnly = True
              PopupMenu = puDimensions
              TabOrder = 0
              Text = '1280'
              OnExit = eWidthExit
            end
            object eHeight: TEdit
              Left = 132
              Top = 24
              Width = 45
              Height = 21
              Alignment = taRightJustify
              NumbersOnly = True
              PopupMenu = puDimensions
              TabOrder = 1
              Text = '1024'
              OnExit = eWidthExit
            end
          end
          object GroupBox1: TGroupBox
            Left = 3
            Top = 383
            Width = 212
            Height = 116
            Caption = 'Palette'
            TabOrder = 2
            object bEditPalette: TSpeedButton
              Left = 6
              Top = 24
              Width = 62
              Height = 22
              Caption = 'Edit'
              ImageIndex = 4
              Images = ImageList1
              OnClick = bEditPaletteClick
            end
            object pbPalette: TPaintBox
              Left = 17
              Top = 58
              Width = 125
              Height = 20
              OnClick = bEditPaletteClick
            end
            object sInfinity: TShape
              Left = 148
              Top = 58
              Width = 20
              Height = 20
              OnMouseDown = sInfinityMouseDown
            end
            object sbLoadPalette: TSpeedButton
              Left = 74
              Top = 24
              Width = 62
              Height = 22
              Caption = 'Open'
              ImageIndex = 7
              Images = ImageList1
              OnClick = sbLoadPaletteClick
            end
            object pbPalette2: TPaintBox
              Left = 17
              Top = 84
              Width = 125
              Height = 20
              OnClick = pbPalette2Click
            end
            object sInfinity2: TShape
              Left = 148
              Top = 84
              Width = 20
              Height = 20
              OnMouseDown = sInfinity2MouseDown
            end
          end
          object gbVarABC: TGroupBox
            Left = 3
            Top = 210
            Width = 212
            Height = 167
            Caption = 'Extra Parameters'
            TabOrder = 3
            object lVarA: TLabel
              Left = 16
              Top = 30
              Width = 6
              Height = 13
              Caption = 'a'
            end
            object lVarB: TLabel
              Left = 16
              Top = 57
              Width = 6
              Height = 13
              Caption = 'b'
            end
            object lVarC: TLabel
              Left = 16
              Top = 84
              Width = 5
              Height = 13
              Caption = 'c'
            end
            object lVarD: TLabel
              Left = 16
              Top = 111
              Width = 6
              Height = 13
              Caption = 'd'
            end
            object lVarE: TLabel
              Left = 16
              Top = 138
              Width = 6
              Height = 13
              Caption = 'e'
            end
            object eVarA: TEdit
              Left = 88
              Top = 27
              Width = 115
              Height = 21
              Hint = 'maps linear palette to exponential palette (default is 1)'
              Alignment = taRightJustify
              PopupMenu = puExamples
              TabOrder = 0
              Text = '1'
              OnExit = eCoeffNExit
            end
            object eVarB: TEdit
              Left = 88
              Top = 54
              Width = 115
              Height = 21
              Alignment = taRightJustify
              PopupMenu = puExamples
              TabOrder = 1
              Text = '1000'
              OnExit = eCoeffNExit
            end
            object eVarC: TEdit
              Left = 88
              Top = 81
              Width = 115
              Height = 21
              Hint = 'maps linear palette to exponential palette (default is 1)'
              Alignment = taRightJustify
              PopupMenu = puExamples
              TabOrder = 2
              Text = '256'
              OnExit = eCoeffNExit
            end
            object eVarD: TEdit
              Left = 88
              Top = 108
              Width = 115
              Height = 21
              Hint = 'maps linear palette to exponential palette (default is 1)'
              Alignment = taRightJustify
              PopupMenu = puExamples
              TabOrder = 3
              Text = '1'
              OnExit = eCoeffNExit
            end
            object eVarE: TEdit
              Left = 88
              Top = 135
              Width = 115
              Height = 21
              Alignment = taRightJustify
              PopupMenu = puExamples
              TabOrder = 4
              Text = '1'
              OnExit = eCoeffNExit
            end
          end
          object GroupBox3: TGroupBox
            Left = 6
            Top = 54
            Width = 212
            Height = 150
            Caption = 'Render'
            TabOrder = 4
            object Label10: TLabel
              Left = 16
              Top = 62
              Width = 44
              Height = 13
              Caption = 'Coeff (n)'
            end
            object Label11: TLabel
              Left = 16
              Top = 89
              Width = 47
              Height = 13
              Caption = 'Iterations'
            end
            object Label12: TLabel
              Left = 16
              Top = 116
              Width = 47
              Height = 13
              Caption = 'Bailout (r)'
            end
            object cbRenderMode: TComboBox
              Left = 16
              Top = 24
              Width = 185
              Height = 21
              Style = csDropDownList
              TabOrder = 0
              OnChange = cbRenderModeChange
            end
            object eCoeffN: TEdit
              Left = 88
              Top = 59
              Width = 115
              Height = 21
              Hint = 'maps linear palette to exponential palette (default is 1)'
              Alignment = taRightJustify
              TabOrder = 1
              Text = '1'
              OnExit = eCoeffNExit
            end
            object eIterations: TEdit
              Left = 88
              Top = 86
              Width = 115
              Height = 21
              Alignment = taRightJustify
              NumbersOnly = True
              TabOrder = 2
              Text = '1000'
              OnExit = eCoeffNExit
            end
            object eBailoutRadius: TEdit
              Left = 88
              Top = 113
              Width = 115
              Height = 21
              Hint = 'maps linear palette to exponential palette (default is 1)'
              Alignment = taRightJustify
              NumbersOnly = True
              TabOrder = 3
              Text = '256'
              OnExit = eCoeffNExit
            end
          end
          object cbFractalSelector: TComboBox
            Left = 53
            Top = 3
            Width = 165
            Height = 21
            Style = csDropDownList
            TabOrder = 5
            OnChange = cbFractalSelectorChange
          end
        end
        object TabSheet2: TTabSheet
          Caption = 'History'
          ImageIndex = 1
          object lbHistory: TListBox
            Left = 0
            Top = 31
            Width = 221
            Height = 749
            Align = alClient
            ItemHeight = 13
            TabOrder = 0
            OnDblClick = lbHistoryDblClick
            ExplicitHeight = 727
          end
          object Panel2: TPanel
            Left = 0
            Top = 0
            Width = 221
            Height = 31
            Align = alTop
            TabOrder = 1
            object sbClearHistory: TSpeedButton
              Left = 188
              Top = 1
              Width = 30
              Height = 27
              Hint = 'clear'
              ImageIndex = 20
              Images = ImageList1
              OnClick = sbClearHistoryClick
            end
            object sbLoadHistory: TSpeedButton
              Left = 4
              Top = 1
              Width = 30
              Height = 27
              Hint = 'clear'
              ImageIndex = 7
              Images = ImageList1
              OnClick = sbLoadHistoryClick
            end
            object sbSaveHistory: TSpeedButton
              Left = 32
              Top = 1
              Width = 30
              Height = 27
              Hint = 'clear'
              ImageIndex = 6
              Images = ImageList1
              OnClick = sbSaveHistoryClick
            end
          end
        end
      end
      object Panel4: TPanel
        Left = 1
        Top = 809
        Width = 229
        Height = 249
        Align = alBottom
        Color = clWhite
        ParentBackground = False
        TabOrder = 1
        ExplicitTop = 819
        object iPreview: TImage
          Left = 14
          Top = 6
          Width = 200
          Height = 200
          Visible = False
        end
      end
    end
  end
  object sbMain: TStatusBar
    Left = 0
    Top = 1095
    Width = 1584
    Height = 19
    Panels = <>
    SimplePanel = True
    ExplicitTop = 1072
  end
  object ImageList1: TImageList
    Left = 1016
    Top = 120
    Bitmap = {
      494C010115001800040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000006000000001002000000000000060
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F3F3F300FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F4FF
      F400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F1FE
      F100FFFFFF0000000000FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F4FF
      F400FFFFFF0000000000FFFFFF0000000000FFFFFF001E1E1E00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F2FF
      F200FFFFFF0000000000FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F2FF
      F200FFFFFF0000000000FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F2FF
      F200FFFFFF0000000000FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F2FF
      F200FFFFFF0000000000FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F4FF
      F400FFFFFF0000000000FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F1FE
      F100FFFFFF0000000000FFFFFF0000000000FFFFFF0000000000FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F0FF
      F000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00050C05000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000F010F002400240000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000005454540000000000000000004444
      4400A7A7A7000000000000000000000000000000000000000000868686002525
      2500000000000000000035353500A3A3A3000000000000000000000000000000
      00000000000000000000000000000F000F000600060000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000008686
      8600000000002E2E2E0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CFCFCF000B0B0B00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007E7E
      7E00000000000000000000000000000000000000000000000000000000003F3F
      3F0000000000AEAEAE0000000000000000000000000000000000000000000000
      00000000000000000000000000002A0F2A00211B210021002100000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D8D8D80000000000BDBDBD00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000545454000404
      0400000000000000000000000000000000000000000000000000000000000000
      0000111111000000000000000000000000000000000000000000000000000000
      0000000000000000000075757500C3C3C300DEDEDE00D7D7D7007A7A7A000C00
      0C00090009000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D3D3
      D30000000000C4C4C40000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000A4A4A4000000000000000000000000000000000000000000717171000000
      00007A7A7A000000000000000000000000000000000000000000000000000000
      000000000000C6C6C600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C5C5
      C500060006000000000000000000000000000000000000000000000000000000
      00005D5D5D002A2A2A0021212100212121006464640000000000D4D4D4000000
      0000BCBCBC000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000004A4A
      4A00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000074747400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00636363000000000000000000000000000000000000000000B3B3B3000000
      000075757500C3C3C300DEDEDE00D7D7D7007A7A7A000C0C0C0009090900E0E0
      E000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B9B9
      B900000000004040400045454500454545004A4A4A001C1C1C00000000004747
      4700000000000000000000000000000000000000000000000000000000001300
      1300E8E8E800FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00EAEAEA000F000F000000000000000000000000000000000000000000C6C6
      C600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C5C5C500060606000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000007070700A0A0A0000000000000000000000000003A3A3A0000000000B5B5
      B500000000000000000000000000000000000C000C0000000000000000001F1F
      1F00EAEAEA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FEFEFE00090909000000000029002900000000005D5D5D0074747400FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00636363005858
      5800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000071717100070707000000000000000000B7B7B70000000000191919000000
      000000000000000000000000000000000000080008000000000000000000130A
      1300CECECE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00EBEBEB001000100000000000000000000000000013131300E8E8E800FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EAEAEA000F0F
      0F00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B3B3B300000000003737370000000000828282000000
      0000000000000000000000000000000000000000000000000000000000000000
      000050505000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0070707000000000000000000000000000000000001F1F1F00EAEAEA00FFFF
      FF000000000000000000000000000000000000000000FFFFFF00FEFEFE000909
      0900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000003A3A3A003B3B3B00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BABABA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B7B7
      B700000000000000000000000000000000000000000013131300CECECE00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EBEBEB001010
      1000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CACACA000000000024242400000000004F4F4F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000010001006F6F6F00D9D9D900F0F0F000D6D6D600848484000000
      000000000000000000000000000000000000000000005050500050505000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00707070005252
      5200000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000353535000000000000000000BEBEBE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000001F001F001C0F1C0020022000000000000000
      000000000000000000000000000000000000000000000000000000000000BABA
      BA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B7B7B700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000AAAAAA00000000002020200000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000D3D3D3000101
      01006F6F6F00D9D9D900F0F0F000D6D6D6008484840000000000D4D4D4000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000E0E0E007878780000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000686868001F1F1F001C1C1C00202020006060600000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000180018001000100000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00668D9E00658C
      9D00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000014141400EEEEEE000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF004E7B8F007FA0
      AF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000919191006E6E6E0000000000E6E6
      E6000000000037373700292929002727270026262600272727002A2A2A002626
      260026262600272727002A2A2A00363636000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00D1F9BC0098F56D0094F7
      6D00CEF9B800FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BABABA008888
      8800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF0095F3660052EA04004AEE
      010057EA0900C9F8B00000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000DFDFDF0015151500F3F3F3000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF0081F1490052EA040050EB
      03005FEB1500AEF5890000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000939393006A6A6A0005050500ECEC
      EC00000000003737370026262600252525002626260025252500252525002525
      2500252525002525250026262600363636000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF007AEE3C0052EB060052EC
      070063EB1B00FEFFFD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BFBFBF008686
      8600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FCFFFB00ACF88D0067F4
      3000FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000DDDDDD0029292900F2F2F2000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000929292006565650000000000F1F1
      F100000000003737370025252500252525002525250025252500262626002626
      2600262626002525250026262600363636000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BCBCBC009595
      9500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000DDDDDD0027272700F1F1F1000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000969696004747470002020200ECEC
      EC00000000003737370025252500262626002525250026262600262626002525
      2500262626002626260026262600363636000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000AAAAAA008C8C
      8C00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000101010001313130011111100111111001111
      1100121212000F0F0F0012121200000000000000000000000000000000000000
      0000010001000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000005050500111111000505050000000000000000000000
      0000000000000000000000000000000000000000000003030300010101000000
      0000000000001E1E1E0001010100000000000000000000000000010101000000
      0000000000000000000000000000000000000000000026262600242424002525
      250026262600252525002323230013131300EAEAEA00F5F5F500F5F5F500F5F5
      F500F5F5F500DBDBDB0024242400000000000000000000000000000000000000
      0000010001000200020000000000000000000000000000000000000000000000
      000000000000CFCFCF000B0B0B00000000000000000000000000000000000000
      00000000000000000000E2E2E200FFFFFF00E1E1E10000000000000000000000
      00000000000000000000000000000000000000000000000000000A0A0A000000
      0000000000000000000003030300000000000000000000000000010101000000
      0000000000000101010000000000000000000000000006060600CCCCCC00E6E6
      E600E5E5E500E5E5E500CDCDCD0024242400F5F5F500FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00F3F3F30027272700000000000000000000000000000000000000
      0000000000000500050000000000000000000000000000000000000000000000
      0000D8D8D80000000000BDBDBD00000000000000000000000000000000000000
      00000000000021212100DEDEDE00F5F5F500DEDEDE0021212100000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000027272700F3F3F300FFFF
      FF00FFFFFF00FFFFFF00F2F2F20027272700E4E4E400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00E5E5E50026262600000000000000000000000000000000000000
      000000000000030003000000000000000000000000000000000000000000D6C2
      D60000000000C4C4C40000000000000000000000000000000000000000000000
      000000000000131313001C1C1C00252525001D1D1D0013131300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000025252500E6E6E600FFFF
      FF00FFFFFF00FFFFFF00E6E6E60025252500E5E5E500FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00E5E5E50026262600000000000300030003000300050005000300
      0300000000000000000002020200020202000101010006000600C1C1C1000000
      0000BCBCBC000000000000000000000000000000000000000000000000000000
      0000D9D9D90014141400E0E0E000E6E6E600DFDFDF0014141400D9D9D9000000
      0000000000000000000000000000000000000000000000000000040404000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000004040400000000000000000026262600E6E6E600FFFF
      FF00FFFFFF00FFFFFF00E5E5E50026262600E5E5E500FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00E5E5E50026262600000000000E000E0002000200010101000000
      000000000000000000000000000001010100040404000101010009090900E0E0
      E000000000000000000000000000000000000000000000000000000000000000
      00005858580048484800FFFFFF00FFFFFF00FFFFFF0048484800585858000000
      0000000000000000000000000000000000000000000003030300161616000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000004040400000000000000000025252500E5E5E500FFFF
      FF00FFFFFF00FFFFFF00E6E6E60026262600E5E5E500FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00E6E6E6002626260000000000000000000000000000000000C6C6
      C6000101010007070700FBFBFB00F7F7F700FFFFFF00C5C5C500060606000000
      000000000000000000000000000000000000000000000000000000000000B7B7
      B70000000000E2E2E200FFFFFF00FFFFFF00FFFFFF00E2E2E20000000000B6B6
      B600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000026262600E5E5E500FFFF
      FF00FFFFFF00FFFFFF00E4E4E40027272700F3F3F300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00F2F2F2002626260000000000000000005D5D5D0074747400FFFF
      FF00010101000C0C0C00FFFFFF00FFFFFF00FFFFFF00FFFFFF00636363005858
      5800000000000000000000000000000000000000000000000000E1E1E1000000
      0000B7B7B700FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B8B8B8000000
      0000E1E1E1000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000026262600E6E6E600FFFF
      FF00FFFFFF00FFFFFF00E5E5E50006060600CCCCCC00E5E5E500E5E5E500E7E7
      E700F4F4F400CECECE0006060600000000000000000013131300E8E8E800FCFC
      FC000202020001010100FFFFFF00FFFFFF00FFFFFF00FFFFFF00EAEAEA000F0F
      0F00000000000000000000000000000000000000000000000000454545005A5A
      5A00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF005B5B
      5B00454545000000000000000000000000000000000002020200010101000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000101010003030300000000000000000022222200E6E6E600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00404040003F3F3F00404040003D3D3D002626
      260011111100212121002525250000000000000000001F1F1F00EAEAEA00C5C5
      C5000404040005050500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE000909
      090000000000000000000000000000000000000000000000000015151500D8D8
      D800FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00D9D9
      D900151515000000000000000000000000000000000001010100040404000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000001C1C1C00000000000000000027272700E6E6E600F5F5
      F500E7E7E700E6E6E600E6E6E600DBDBDB00CDCDCD00CCCCCC00DADADA00CDCD
      CD00050505000000000000000000000000000000000013131300CECECE00FAFA
      FA00EEEEEE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EBEBEB001010
      100000000000000000000000000000000000000000000000000028222800F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F4F4
      F400232323000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000043434300E6E6E6004343
      43003B3B3B003F3F3F00272727003F3F3F0056565600535353005A5A5A00F5F5
      F50045454500000000000000000000000000000000005050500050505000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00707070005252
      520000000000000000000000000000000000000000000000000016161600DADA
      DA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00DADA
      DA00161616000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000027272700B1B1B1000404
      0400B4B4B400DBDBDB00E7E7E700E7E7E700DBDBDB00B4B4B40005050500B1B1
      B10027272700000000000000000000000000000000000000000000000000BABA
      BA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B7B7B700000000000000
      00000000000000000000000000000000000000000000000000003D3D3D006262
      6200FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF006262
      62003D3D3D000000000000000000000000000000000000000000000000000000
      0000000000000F0F0F0011111100000000000000000003030300010101000000
      000000000000000000000A0A0A000000000000000000272727001E1E1E001818
      18003131310037373700FFFFFF00FFFFFF003737370032323200181818001F1F
      1F00272727000000000000000000000000000000000000000000D3D3D3000101
      01006F6F6F00D9D9D900F0F0F000D6D6D6008484840000000000D4D4D4000000
      0000000000000000000000000000000000000000000000000000DADADA000000
      0000B3B3B300FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B4B4B4000000
      0000DADADA000000000000000000000000000000000000000000000000000000
      0000000000000000000003030300000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000DDDDDD0000000000C9C9C900C8C8C80000000000DEDEDE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000686868001F1F1F001C1C1C00202020006060600000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B2B2
      B200000000006D6D6D00D5D5D500F5F5F500D5D5D5006C6C6C0000000000B2B2
      B200000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BCBCBC000808080009090900BCBCBC0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000DBDBDB004F4F4F001F1F1F00111111001F1F1F0050505000DBDBDB000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000002D2D2D78000000F10101
      01F1000000F1000000F1000000F1000000F1000000F1000000F1000000F10000
      00F1000000F1000000F1000000F1000000E40000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000013131377000000FFD1D1D1FF5F5F
      5FFF6E6E6EFFB2B2B2FF0C0C0CFFDDDDDDFFDDDDDDFFDDDDDDFF272727FF6E6E
      6EFFDDDDDDFFDDDDDDFFC0C0C0FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A0A0A0001A1A1A002222
      22002E2E2E00222222001B1B1B001D1D1D001D1D1D001D1D1D001D1D1D001F1F
      1F000F0F0F001B1B1B0000000000000000001313130026262600252525002626
      2600262626002525250026262600262626002525250027272700515151000505
      050000000000272727004848480015151500000000FFC4C4C4FFFFFFFFFF5D5D
      5DFF919191FFD7D7D7FF000000FFFFFFFFFFFFFFFFFFFFFFFFFF333333FF8A8A
      8AFFFFFFFFFFFFFFFFFFF1F1F1FF000000F11111110036363600272727002626
      2600252525002525250026262600262626002626260026262600252525002424
      240038383800000000000000000000000000000000009E9E9E001D1D1D00F3F3
      F300FAFAFA00FFFFFF00FFFFFF00FAFAFA00F3F3F300F5F5F500F5F5F500FFFF
      FF00EBEBEB001D1D1D00000000000000000000000000DBDBDB00E5E5E500E5E5
      E500E6E6E600E5E5E500E5E5E500E5E5E500E6E6E600FFFFFF00989898000000
      0000ABABAB00FDFDFD00A8A8A80000000000000000F5EEEEEEFFFFFFFFFF4848
      48FF737373FFFFFFFFFFD1D1D1FFFFFFFFFFFFFFFFFFFFFFFFFF363636FF7777
      77FFFFFFFFFFFFFFFFFFDDDDDDFF000000F1000000006F6F6F00F2F2F200E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E6E6E600E5E5E500E4E4
      E40000000000919191000000000000000000000000009B9B9B002A2A2A00F4F4
      F4009191910054545400A5A5A500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F5001D1D1D00000000000000000013131300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CBCBCB0004040400BCBC
      BC00FFFFFF00CDCDCD000000000013131300000000F1DDDDDDFFFFFFFFFF5050
      50FF000000FF8A8A8AFFA8A8A8FF7F7F7FFF7F7F7FFF7F7F7FFF000000FF7F7F
      7FFFFFFFFFFFFFFFFFFFDDDDDDFF000000F10202020000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00B6B6B600000000000000000000000000000000009696960020202000FAFA
      FA00727272002F2F2F003636360038383800FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F5F5F5001D1D1D00000000000000000013131300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C4C4C400000000007E7E7E00FFFF
      FF00B3B3B30000000000A9A9A9003D3D3D00000000F1DDDDDDFFFFFFFFFFB3B3
      B3FF565656FF2E2E2EFF2E2E2EFF2E2E2EFF2E2E2EFF2E2E2EFF5D5D5DFFC7C7
      C7FFFFFFFFFFFFFFFFFFDDDDDDFF000000F14B4B4B003232320066666600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000C0C0C008F8F8F0000000000000000009D9D9D001D1D1D00FFFF
      FF00A0A0A00044444400FFFFFF004141410020202000FFFFFF00FFFFFF00FFFF
      FF00F5F5F5001D1D1D00000000000000000000000000C3C3C300FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00B5B5B5000000000089898900404040007A7A
      7A0000000000C1C1C100FFFFFF0010101000000000F1DCDCDCFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFDCDCDCFF000000F13E3E3E00DBDBDB0000000000E6E6
      E600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00B6B6B6000000000000000000000000009E9E9E001D1D1D00FCFC
      FC00FEFEFE003232320041414100FFFFFF004242420020202000FFFFFF00FFFF
      FF00F5F5F5001D1D1D0000000000000000001111110000000000BEBEBE00FFFF
      FF00FFFFFF00FFFFFF00B6B6B60000000000B2B2B200FFFFFF00BABABA000000
      0000BEBEBE00FFFFFF00F6F6F60010101000000000F1DFDFDFFFFAFAFAFFF3F3
      F3FFF0F0F0FFF0F0F0FFF0F0F0FFF0F0F0FFF0F0F0FFF0F0F0FFF0F0F0FFEEEE
      EEFFF1F1F1FFFAFAFAFFDFDFDFFF000000F10E0E0E00FFFFFF00666666004949
      4900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00292929008F8F8F00000000009E9E9E001D1D1D00F6F6
      F600FDFDFD00FFFFFF002020200042424200FFFFFF004242420020202000FFFF
      FF00FEFEFE001D1D1D0000000000000000003E3E3E00AAAAAA0000000000B2B2
      B200FFFFFF00B2B2B20000000000B5B5B500FFFFFF00FFFFFF00FFFFFF00FAFA
      FA00FFFFFF00FFFFFF00F3F3F30011111100000000F1F4F4F4FF8A8A8AFF0A0A
      0AFF020202FF020202FF020202FF020202FF020202FF020202FF020202FF0202
      02FF0A0A0AFF8A8A8AFFF4F4F4FF000000F10E0E0E00FFFFFF00F0F0F0000000
      0000C3C3C300E6E6E600E5E5E500E5E5E500E6E6E600E6E6E600E5E5E500E8E8
      E800F3F3F300EBEBEB00A1A1A10000000000000000009E9E9E001D1D1D00F5F5
      F500FFFFFF00FFFFFF00FFFFFF002020200042424200FFFFFF00424242003B3B
      3B00FCFCFC002F2F2F0000000000000000000F0F0F00FFFFFF00C1C1C1000000
      00007979790000000000B5B5B500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00EFEFEF00FEFEFE00F6F6F60012121200000000F1F7F7F7FF4F4F4FFF5858
      58FFCECECEFFCECECEFFCECECEFFCECECEFFCECECEFFCECECEFFCECECEFFCECE
      CEFF585858FF4F4F4FFFF7F7F7FF000000F111111100F6F6F600FFFFFF009393
      9300070707002626260026262600262626002626260026262600262626002424
      240014141400242424004343430048484800000000009E9E9E001D1D1D00F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF002020200042424200FFFFFF005757
      5700151515003636360000000000000000000F0F0F00F6F6F600FFFFFF00BDBD
      BD0000000000BEBEBE00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EDED
      ED006D6D6D00FAFAFA00FDFDFD0011111100000000F1F6F6F6FF4E4E4EFF8A8A
      8AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFF8A8A8AFF4E4E4EFFF6F6F6FF000000F112121200F4F4F400FFFFFF00FFFF
      FF00EBEBEB00EFEFEF00F5F5F500F5F5F500F5F5F500F5F5F500F5F5F500DADA
      DA0004040400CBCBCB000000000000000000000000009E9E9E001D1D1D00F5F5
      F500FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00373737004F4F4F00FFFF
      FF006464640008080800000000000000000013131300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FCFCFC00FFFFFF00FFFFFF0013131300000000F1F6F6F6FF545454FF7F7F
      7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFF7F7F7FFF545454FFF6F6F6FF000000F113131300FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00F5F5F500F5F5F500F5F5F500F5F5F500F5F5F500DADA
      DA0000000000000000000000000000000000000000009E9E9E0021212100F7F7
      F700F9F9F900F7F7F700F6F6F600F6F6F600FFFFFF00FFFFFF00151515005C5C
      5C00FFFFFF0089898900595959000000000000000000DCDCDC00E5E5E500E7E7
      E700F2F2F200E7E7E700E6E6E600E6E6E600E5E5E500E5E5E500E5E5E500E7E7
      E700EFEFEF00E6E6E600DBDBDB0000000000000000F1F6F6F6FF545454FF7F7F
      7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFF7F7F7FFF545454FFF6F6F6FF000000F100000000DBDBDB00E6E6E600E5E5
      E500AAAAAA002424240026262600262626002525250026262600252525002424
      24005959590000000000000000000000000000000000A3A3A3001B1B1B002121
      21001E1E1E0014141400202020002A2A2A00131313003A3A3A003F3F3F000A0A
      0A008D8D8D00F3F3F30015151500000000001313130026262600252525002626
      2600252525002626260025252500262626002525250026262600252525002626
      260025252500252525002626260012121200000000F2FFFFFFFF5C5C5CFF8A8A
      8AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFF8A8A8AFF5C5C5CFFFFFFFFFF000000F25252520026262600262626002525
      250024242400AAAAAA0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00005A5A5A000A0A0A0088888800000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FFD5D5D5FF474747FF6E6E
      6EFFDDDDDDFFDDDDDDFFDDDDDDFFDDDDDDFFDDDDDDFFDDDDDDFFDDDDDDFFDDDD
      DDFF6E6E6EFF474747FFD5D5D5FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000D0D0DB2000000F1000000F10000
      00F1000000F1000000F1000000F1000000F1000000F1000000F1000000F10000
      00F1000000F1000000F1000000F10D0D0DB20000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000AFAFAF006C6C6C003939390017171700202020000F0F0F0064646400C7C7
      C700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CFCFCF000B0B0B00000000000000000000000000000000008B8B
      8B00060606005A5A5A00DCDCDC000000000000000000D7D7D7008D8D8D000404
      0400777777000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D8D8D80000000000BDBDBD00000000000000000000000000111111002323
      2300000000000000000000000000000000000000000000000000000000000000
      0000242424001919190000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D3D3
      D30000000000C4C4C40000000000000000000000000062626200191919000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000005252520074747400000000000000000000000000000000000000
      0000D5D5D5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D5D5
      D500000000000000000000000000000000000000000000000000000000000000
      00005D5D5D002A2A2A0021212100212121006464640000000000D4D4D4000000
      0000BCBCBC00000000000000000000000000D7D7D70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000D3D3D3000000000000000000000000006C6C
      6C000F0F0F000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001010
      10006B6B6B000000000000000000000000000000000000000000B3B3B3000000
      000075757500C3C3C300DEDEDE00D7D7D7007A7A7A000C0C0C0009090900E0E0
      E000000000000000000000000000000000006161610065656500000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A2A2A200575757000000000000000000757575000000
      0000DADADA000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DADA
      DA0000000000767676000000000000000000000000000000000000000000C6C6
      C600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C5C5C500060606000000
      00000000000000000000000000000000000015151500E3E3E300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000DDDDDD000E0E0E000000000088888800212121000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000222222008888880000000000000000005D5D5D0074747400FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00636363005858
      5800000000000000000000000000000000001414140000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000262626007F7F7F00000000005C5C5C007E7E
      7E00666666006666660066666600666666006767670066666600666666006666
      6600666666006666660066666600666666006666660066666600666666006767
      6700666666006666660066666600666666006666660066666600666666006666
      66007E7E7E005C5C5C00000000007F7F7F000000000013131300E8E8E800FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EAEAEA000F0F
      0F00000000000000000000000000000000001D1D1D0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000001C1C1C007F7F7F00000000005C5C5C007E7E
      7E00666666006666660066666600666666006666660066666600666666006666
      6600676767006666660066666600666666006666660066666600666666006666
      6600666666006666660066666600676767006666660066666600666666006666
      66007E7E7E005C5C5C00000000007F7F7F00000000001F1F1F00EAEAEA00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FEFEFE000909
      0900000000000000000000000000000000000F0F0F00CFCFCF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000EBEBEB000A0A0A000000000088888800222222000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000002121210088888800000000000000000013131300CECECE00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00EBEBEB001010
      1000000000000000000000000000000000002D2D2D008D8D8D00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000008C8C8C00282828000000000000000000767676000000
      0000DADADA000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DADA
      DA0000000000757575000000000000000000000000005050500050505000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00707070005252
      520000000000000000000000000000000000B9B9B90000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000F9F9F90000000000C2C2C2000000000000000000000000006B6B
      6B00101010000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000F0F
      0F006C6C6C00000000000000000000000000000000000000000000000000BABA
      BA00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B7B7B700000000000000
      0000000000000000000000000000000000000000000046464600676767000000
      0000000000001E1E1E0000000000000000000000000000000000000000000000
      000000000000464646005B5B5B00000000000000000000000000000000000000
      0000D5D5D5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D5D5
      D500000000000000000000000000000000000000000000000000D3D3D3000101
      01006F6F6F00D9D9D900F0F0F000D6D6D6008484840000000000D4D4D4000000
      0000000000000000000000000000000000000000000000000000323232008A8A
      8A00000000002424240000000000000000000000000000000000000000000000
      0000343434002E2E2E0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000686868001F1F1F001C1C1C00202020006060600000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001C1C
      1C00151515003030300000000000000000000000000000000000565656000000
      0000707070000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000343434004343
      430001010100151515000000000000000000000000000000000069696900A7A7
      A700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000600000000100010000000000000300000000000000000000
      000000000000000000000000FFFFFF00E00F000000000000C007000000000000
      C007000000000000C007000000000000C007000000000000C007000000000000
      C007000000000000C007000000000000C007000000000000C007000000000000
      C007000000000000C007000000000000C0070000000000008003000000000000
      F83F000000000000FC7F000000000000FFFF07C07E7EFFFFFFFF9FE3FFFDFFF9
      DFFFCFE3FE3BFFF19FFFCFE7F807FFE30000E7C7F007F0479FFFE00FF007C00F
      DFFFE00FE003C01FFFFFF38F6002800FFFFFF31F6002800FFFFBF91FF007800F
      FFF9F93FF007800F0000F83FF80F800FFFF9FC3FFE3FC01FFFFBFC7FFFFFC01F
      FFFFFE7FFFFFF07FFFFFFFFF7E7EFFFFFFFFFE7FFE01FF00FFFFFC3F8001FF7E
      9FFFF99F8001FF7E0800FBDF8001FF7ECFFFFFFF8001FFFE1FFFCFF38001FC3E
      08009FF98001F99ACFFF3E7C8001DBD01FFF3E7C80010BDB08009FF98001599F
      CFFFCFF380077C3F1FFFFFFF80077FFF0800FBDF80077EFFCFFFF99F80077EFF
      FFFFFC3FF87F7EFFFFFFFE7FFCFF00FFFFFFFE01F3FFFC7F99998001F3F9F83F
      99998001F3F1F83FFFFF8001F3E3F83FFFFF80010007F01F9FF98001000FF01F
      9FF98001C01FE00FFFFF8001800FC007FFFF8001800FC0079FF98001800FC007
      9FF98007800FC007FFFF8007800FC007FFFF8007C01FC00799998007C01FC007
      9999F03FF07FE00FFFFFF87FFFFFF01FFFFFFFFF0000FFFFFFFFFFFF0000FFFF
      8003000000000007800300000000000380030000000000038003000000000001
      8003000000000001800300000000000080030000000000008003000000000000
      80030000000000038003000000000007800100000000000780010000000003FF
      FFF1FFFF0000FFFFFFFFFFFF0000FFFFFFFFF00FFFFFFFFFFFF9E187FFFFFFFF
      FFF1CFF3FFFFFFFFFFE39FF9F7FFFFEFF0473FFCE7FFFFE7C00F3FFCC7FFFFE3
      C01F3FFC9FFFFFF9800F7FFE00000000800F7FFE00000000800F3FFC9FFFFFF9
      800F3FFCC7FFFFE3800F3FF8E7FFFFE7C01F9BF9F7FFFFEFC01FCBF3FFFFFFFF
      F07FE3C7FFFFFFFFFFFFC3CFFFFFFFFF00000000000000000000000000000000
      000000000000}
  end
  object puDimensions: TPopupMenu
    Left = 832
    Top = 80
    object Dimensions1: TMenuItem
      Caption = 'Dimensions'
      Enabled = False
    end
    object Dimensions2: TMenuItem
      Caption = '-'
    end
    object miDimensions: TMenuItem
      Caption = 'Desktop'
      object miDesktopDimension: TMenuItem
        Caption = '1024 x 768'
        OnClick = miDesktopDimensionClick
      end
      object N1024x7682: TMenuItem
        Tag = 1
        Caption = '1280 x 720'
        OnClick = miDesktopDimensionClick
      end
      object N1280x8001: TMenuItem
        Tag = 2
        Caption = '1280 x 800'
        OnClick = miDesktopDimensionClick
      end
      object N1280x8002: TMenuItem
        Tag = 3
        Caption = '1280 x 1024'
        OnClick = miDesktopDimensionClick
      end
      object N1360x7681: TMenuItem
        Tag = 4
        Caption = '1360 x 768'
        OnClick = miDesktopDimensionClick
      end
      object N1360x7682: TMenuItem
        Tag = 5
        Caption = '1366 x 768'
        OnClick = miDesktopDimensionClick
      end
      object N1440x9001: TMenuItem
        Tag = 6
        Caption = '1440 x 900'
        OnClick = miDesktopDimensionClick
      end
      object N1440x9002: TMenuItem
        Tag = 7
        Caption = '1600 x 900'
        OnClick = miDesktopDimensionClick
      end
      object N1680x10501: TMenuItem
        Tag = 8
        Caption = '1680 x 1050'
        OnClick = miDesktopDimensionClick
      end
      object N1920x10801: TMenuItem
        Tag = 9
        Caption = '1920 x 1200'
        OnClick = miDesktopDimensionClick
      end
      object N1920x12001: TMenuItem
        Tag = 10
        Caption = '1920 x 1080'
        OnClick = miDesktopDimensionClick
      end
      object N2560x14401: TMenuItem
        Tag = 11
        Caption = '2560 x 1440'
        OnClick = miDesktopDimensionClick
      end
      object N2560x10801: TMenuItem
        Tag = 12
        Caption = '2560 x 1080'
        OnClick = miDesktopDimensionClick
      end
      object N2560x18001: TMenuItem
        Tag = 13
        Caption = '2560 x 1800'
        OnClick = miDesktopDimensionClick
      end
      object N2880x18001: TMenuItem
        Tag = 14
        Caption = '2880 x 1800'
        OnClick = miDesktopDimensionClick
      end
      object N3440x14401: TMenuItem
        Tag = 15
        Caption = '3440 x 1440'
        OnClick = miDesktopDimensionClick
      end
      object N3840x21601: TMenuItem
        Tag = 16
        Caption = '3840 x 2160'
        OnClick = miDesktopDimensionClick
      end
    end
    object Mobilephone1: TMenuItem
      Caption = 'Mobile phone'
      object miMobileDimensions: TMenuItem
        Caption = 'iPhone 11 (828 x 1792)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone11Pro1125x24361: TMenuItem
        Tag = 1
        Caption = 'iPhone 11 Pro (1125 x 2436)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone11Pro1125x24362: TMenuItem
        Tag = 2
        Caption = 'iPhone 11 Pro Max (1242 x 2688)'
        OnClick = miMobileDimensionsClick
      end
      object iPhoneSE2020750x13341: TMenuItem
        Tag = 3
        Caption = 'iPhone SE (2020) (750 x 1334)'
        OnClick = miMobileDimensionsClick
      end
      object iPhoneSE2020750x13342: TMenuItem
        Tag = 4
        Caption = 'iPhone 12'#9' (1170 x 2532)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone12mini1125x24361: TMenuItem
        Tag = 5
        Caption = 'iPhone 12 mini (1125 x 2436)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone12mini1125x24362: TMenuItem
        Tag = 6
        Caption = 'iPhone 12 Pro (1170 x 2532)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone12ProMax1284x27781: TMenuItem
        Tag = 7
        Caption = 'iPhone 12 Pro Max (1284 x 2778)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone12ProMax1284x27782: TMenuItem
        Tag = 8
        Caption = 'iPhone 13'#9' (1170 x 2532)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone13mini1080x23401: TMenuItem
        Tag = 9
        Caption = 'iPhone 13 mini (1080 x 2340)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone13mini1080x23402: TMenuItem
        Tag = 10
        Caption = 'iPhone 13 Pro (1170 x 2532)'
        OnClick = miMobileDimensionsClick
      end
      object iPhone13ProMax1284x27781: TMenuItem
        Tag = 11
        Caption = 'iPhone 13 Pro Max (1284 x 2778)'
        OnClick = miMobileDimensionsClick
      end
    end
    object N13: TMenuItem
      Caption = '-'
    end
    object exture1: TMenuItem
      Caption = 'Texture'
      object miTextureDimensions: TMenuItem
        Caption = '128 x 128'
        OnClick = miTextureDimensionsClick
      end
      object N128x1282: TMenuItem
        Tag = 1
        Caption = '256 x 256'
        OnClick = miTextureDimensionsClick
      end
      object N128x1283: TMenuItem
        Tag = 2
        Caption = '512 x 512'
        OnClick = miTextureDimensionsClick
      end
      object N128x1284: TMenuItem
        Tag = 3
        Caption = '1024 x 1024'
        OnClick = miTextureDimensionsClick
      end
      object N128x1285: TMenuItem
        Tag = 4
        Caption = '2048 x 2048'
        OnClick = miTextureDimensionsClick
      end
      object N128x1286: TMenuItem
        Tag = 5
        Caption = '4096 x 4096'
        OnClick = miTextureDimensionsClick
      end
    end
    object N19: TMenuItem
      Caption = '-'
    end
    object Resize1: TMenuItem
      Caption = 'Resize'
      object Quarter1: TMenuItem
        Caption = 'Quarter (x0.25)'
        OnClick = Half2Click
      end
      object Half1: TMenuItem
        Tag = 1
        Caption = 'Half (x0.5)'
        OnClick = Half2Click
      end
      object Half2: TMenuItem
        Tag = 2
        Caption = 'Double (x2)'
        OnClick = Half2Click
      end
      object Quadruplex41: TMenuItem
        Tag = 3
        Caption = 'Quadruple (x4)'
        OnClick = Half2Click
      end
    end
  end
  object MainMenu1: TMainMenu
    Tag = 3
    Left = 672
    Top = 80
    object File1: TMenuItem
      Caption = 'File'
      object File2: TMenuItem
        Caption = 'Open Project...'
        OnClick = bOpenProjectClick
      end
      object Saveproject1: TMenuItem
        Caption = 'Save Project...'
        OnClick = bSaveProjectClick
      end
      object N9: TMenuItem
        Caption = '-'
      end
      object miSaveFractalParameters: TMenuItem
        Caption = 'Save fractal parameters...'
        OnClick = miSaveFractalParametersClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object N2: TMenuItem
        Caption = 'Export...'
        OnClick = sbSaveImageClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object N4: TMenuItem
        Caption = 'Exit'
      end
    end
    object Edity1: TMenuItem
      Caption = 'Edit'
      object Copyboundstoclipboard1: TMenuItem
        Caption = 'Copy bounds to clipboard'
        OnClick = sbCopyBoundsToClipboardClick
      end
      object miCopyAllToClipboard: TMenuItem
        Caption = 'Copy all parameters to clipboard'
        OnClick = miCopyAllToClipboardClick
      end
      object N18: TMenuItem
        Caption = '-'
      end
      object miCopyToClipboard: TMenuItem
        Caption = 'Copy render to clipboard'
        OnClick = miCopyToClipboardClick
      end
      object N14: TMenuItem
        Caption = '-'
      end
      object QuickParameter1: TMenuItem
        Caption = 'Quick Parameter (fine)'
        object miQPA: TMenuItem
          AutoCheck = True
          Caption = '0.01'
          Checked = True
          RadioItem = True
          OnClick = miQPAClick
        end
        object miQPB: TMenuItem
          Tag = 1
          AutoCheck = True
          Caption = '0.001'
          RadioItem = True
          OnClick = miQPAClick
        end
        object miQPC: TMenuItem
          Tag = 2
          AutoCheck = True
          Caption = '0.0001'
          RadioItem = True
          OnClick = miQPAClick
        end
        object miQPD: TMenuItem
          Tag = 3
          AutoCheck = True
          Caption = '0.00001'
          RadioItem = True
          OnClick = miQPAClick
        end
        object miQPE: TMenuItem
          Tag = 4
          AutoCheck = True
          Caption = '0.000001'
          RadioItem = True
          OnClick = miQPAClick
        end
      end
      object N17: TMenuItem
        Caption = '-'
      end
      object miRecolour: TMenuItem
        AutoCheck = True
        Caption = 'Recolour fractal after palette change'
        Checked = True
      end
    end
    object Export1: TMenuItem
      Caption = 'Export'
      object miSaveAllImages: TMenuItem
        AutoCheck = True
        Caption = 'Save all generated images'
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object miSaveParameters: TMenuItem
        AutoCheck = True
        Caption = 'Save parameters with image'
      end
      object N11: TMenuItem
        Caption = '-'
      end
      object miConfigAnimation: TMenuItem
        Caption = 'Configure animation...'
        OnClick = miConfigAnimationClick
      end
    end
    object ools1: TMenuItem
      Caption = 'Tools'
      object Resetparameters1: TMenuItem
        Caption = 'Reset parameters'
        OnClick = sbResetClick
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object N6: TMenuItem
        Caption = 'Zoom at point'
        ShortCut = 16474
        OnClick = sbZoomClick
      end
      object Zoomintoarea1: TMenuItem
        Caption = 'Zoom into area'
        ShortCut = 32858
        OnClick = sbZoomCropClick
      end
      object N8: TMenuItem
        Caption = '-'
      end
      object miRMBSetParameters: TMenuItem
        AutoCheck = True
        Caption = 'RMB on image sets parameters'
      end
    end
    object Render1: TMenuItem
      Caption = 'Render'
      object Render2: TMenuItem
        Caption = 'Render'
        ShortCut = 116
        OnClick = sbRenderClick
      end
      object N16: TMenuItem
        Caption = '-'
      end
      object miSuperSample: TMenuItem
        AutoCheck = True
        Caption = 'Super-sample'
        OnClick = miSuperSampleClick
      end
      object Samples1: TMenuItem
        Caption = 'Samples'
        object miSamples4: TMenuItem
          Caption = '4'
          GroupIndex = 1
          RadioItem = True
          OnClick = miSamples4Click
        end
        object miSamples8: TMenuItem
          Tag = 1
          Caption = '8'
          Checked = True
          GroupIndex = 1
          RadioItem = True
          OnClick = miSamples4Click
        end
        object miSamples16: TMenuItem
          Tag = 2
          Caption = '16'
          GroupIndex = 1
          RadioItem = True
          OnClick = miSamples4Click
        end
        object miSamples32: TMenuItem
          Tag = 3
          Caption = '32'
          GroupIndex = 1
          RadioItem = True
          OnClick = miSamples4Click
        end
        object miSamples64: TMenuItem
          Tag = 4
          Caption = '64'
          GroupIndex = 1
          RadioItem = True
          OnClick = miSamples4Click
        end
      end
      object N10: TMenuItem
        Caption = '-'
      end
      object miRenderAnimation: TMenuItem
        Caption = 'Animation'
        OnClick = eAnimationClick
      end
      object N15: TMenuItem
        Caption = '-'
      end
      object miShowPreview: TMenuItem
        AutoCheck = True
        Caption = 'Show preview'
        OnClick = miShowPreviewClick
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Caption = 'About'
        OnClick = sbAboutClick
      end
    end
  end
  object puExamples: TPopupMenu
    Left = 752
    Top = 82
    object JuliaSets1: TMenuItem
      Caption = 'Julia'
      object miExampleJS1: TMenuItem
        Caption = '-0.79, 0.15'
        OnClick = miExampleJS1Click
      end
      object N1621041: TMenuItem
        Tag = 1
        Caption = '-0.162, 1.04'
        OnClick = miExampleJS1Click
      end
      object N3011: TMenuItem
        Tag = 2
        Caption = '0.3, -0.01'
        OnClick = miExampleJS1Click
      end
      object N147601: TMenuItem
        Tag = 3
        Caption = '-1.476, 0'
        OnClick = miExampleJS1Click
      end
      object N12771: TMenuItem
        Tag = 4
        Caption = '-0.12, -0.77'
        OnClick = miExampleJS1Click
      end
      object N280081: TMenuItem
        Tag = 5
        Caption = '0.28, 0.008'
        OnClick = miExampleJS1Click
      end
      object N0081: TMenuItem
        Tag = 6
        Caption = '0, 0.8'
        OnClick = miExampleJS1Click
      end
      object N037011: TMenuItem
        Tag = 7
        Caption = '0.37, 0.1'
        OnClick = miExampleJS1Click
      end
      object N035503551: TMenuItem
        Tag = 8
        Caption = '0.355, 0.355'
        OnClick = miExampleJS1Click
      end
      object N0540541: TMenuItem
        Tag = 9
        Caption = '-0.54, 0.54'
        OnClick = miExampleJS1Click
      end
      object N040591: TMenuItem
        Tag = 10
        Caption = '-0.4, -0.59'
        OnClick = miExampleJS1Click
      end
      object N0340051: TMenuItem
        Tag = 11
        Caption = '0.34, -0.05'
        OnClick = miExampleJS1Click
      end
      object N035553403372921: TMenuItem
        Tag = 12
        Caption = '0.355534, 0.337292'
        OnClick = miExampleJS1Click
      end
      object N01621041: TMenuItem
        Tag = 13
        Caption = '-0.162, 1.04'
        OnClick = miExampleJS1Click
      end
      object N0790151: TMenuItem
        Tag = 14
        Caption = '-0.79, 0.15'
        OnClick = miExampleJS1Click
      end
      object N03300081: TMenuItem
        Tag = 15
        Caption = '0.33, 0.008'
        OnClick = miExampleJS1Click
      end
      object N0745430113011: TMenuItem
        Tag = 16
        Caption = '-0.74543, 0.11301'
        OnClick = miExampleJS1Click
      end
      object N0801561: TMenuItem
        Tag = 17
        Caption = '-0.8, 0.156'
        OnClick = miExampleJS1Click
      end
      object N0260541: TMenuItem
        Tag = 18
        Caption = '0.26, 0.54'
        OnClick = miExampleJS1Click
      end
      object N1040041: TMenuItem
        Tag = 19
        Caption = '-1.04, 0.04'
        OnClick = miExampleJS1Click
      end
      object N1135024751: TMenuItem
        Tag = 20
        Caption = '-1.135, 0.2475'
        OnClick = miExampleJS1Click
      end
      object N11825031751: TMenuItem
        Tag = 21
        Caption = '-1.1825, 0.3175'
        OnClick = miExampleJS1Click
      end
      object N072032751: TMenuItem
        Tag = 22
        Caption = '-0.72, -0.3275'
        OnClick = miExampleJS1Click
      end
      object N11767506451: TMenuItem
        Tag = 23
        Caption = '-1.17675, 0.645'
        OnClick = miExampleJS1Click
      end
      object N101: TMenuItem
        Tag = 24
        Caption = '-1, 0'
        OnClick = miExampleJS1Click
      end
      object N102: TMenuItem
        Tag = 25
        Caption = '0.3, 0.6'
        OnClick = miExampleJS1Click
      end
      object N0801562: TMenuItem
        Tag = 26
        Caption = '0.8, 0.156'
        OnClick = miExampleJS1Click
      end
      object N027930011: TMenuItem
        Tag = 27
        Caption = '0.2793, -0.01'
        OnClick = miExampleJS1Click
      end
    end
    object JuliaCubic1: TMenuItem
      Caption = 'Julia Cubic'
      object miExampleJC1: TMenuItem
        Caption = '-1.5855, 0.6877'
        OnClick = miExampleJC1Click
      end
      object miExampleJC2: TMenuItem
        Tag = 1
        Caption = '0.859, 0.7157'
        OnClick = miExampleJC1Click
      end
      object miExampleJC3: TMenuItem
        Tag = 2
        Caption = '-0.748, -1.309'
        OnClick = miExampleJC1Click
      end
      object miExampleJC4: TMenuItem
        Tag = 3
        Caption = '-0.349, 1.291'
        OnClick = miExampleJC1Click
      end
      object miExampleJC5: TMenuItem
        Tag = 4
        Caption = '-1.249, 1.092'
        OnClick = miExampleJC1Click
      end
      object N1659068071: TMenuItem
        Tag = 5
        Caption = '-1.659, 0.6807'
        OnClick = miExampleJC1Click
      end
      object N1659068072: TMenuItem
        Tag = 6
        Caption = '-1.659, 0.5807'
        OnClick = miExampleJC1Click
      end
      object N0789131631: TMenuItem
        Tag = 7
        Caption = '-0.789, -1.3163'
        OnClick = miExampleJC1Click
      end
      object N0789131632: TMenuItem
        Tag = 8
        Caption = '-0.394, -1.2243'
        OnClick = miExampleJC1Click
      end
      object N16070611: TMenuItem
        Tag = 9
        Caption = '-1.6, 0.7061'
        OnClick = miExampleJC1Click
      end
    end
    object N12: TMenuItem
      Caption = '-'
    end
    object Martin1: TMenuItem
      Caption = 'Martin'
      object miExampleM1: TMenuItem
        Caption = '68, 75, 83'
        OnClick = miExampleM1Click
      end
      object N6875832: TMenuItem
        Tag = 1
        Caption = '90, 30, 10'
        OnClick = miExampleM1Click
      end
      object N10101001: TMenuItem
        Tag = 2
        Caption = '10, -10, 100'
        OnClick = miExampleM1Click
      end
      object N2004801: TMenuItem
        Tag = 3
        Caption = '-200, -4, -80'
        OnClick = miExampleM1Click
      end
      object N1371741: TMenuItem
        Tag = 4
        Caption = '-137, 17, -4'
        OnClick = miExampleM1Click
      end
      object N10100101: TMenuItem
        Tag = 5
        Caption = '10, 100, -10'
        OnClick = miExampleM1Click
      end
      object N10100102: TMenuItem
        Tag = 6
        Caption = '-137, 17, 4'
        OnClick = miExampleM1Click
      end
      object N12182561: TMenuItem
        Tag = 7
        Caption = '12, 18, 256'
        OnClick = miExampleM1Click
      end
    end
  end
  object odPalette: TOpenDialog
    DefaultExt = 'palette'
    Filter = 'Pretty Chaos Palette files (*.palette)|*.palette'
    Left = 904
    Top = 64
  end
end
