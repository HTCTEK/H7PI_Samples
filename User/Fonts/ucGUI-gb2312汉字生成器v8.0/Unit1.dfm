object Form1: TForm1
  Left = 320
  Top = 146
  Width = 1022
  Height = 657
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 441
    Top = 0
    Height = 619
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 441
    Height = 619
    Align = alLeft
    TabOrder = 0
    object Memo1: TMemo
      Left = 1
      Top = 88
      Width = 439
      Height = 507
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
      OnChange = Memo1Change
    end
    object Left_Top_Panel: TPanel
      Left = 1
      Top = 1
      Width = 439
      Height = 87
      Align = alTop
      TabOrder = 1
      object Label1: TLabel
        Left = 5
        Top = 70
        Width = 329
        Height = 13
        AutoSize = False
        Caption = #25353#19978#38754#25353#38062#29983#25104#25991#23383#12289#25110#32773#25163#21160#36755#20837#25991#23383#65306
        Color = clBtnFace
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clMenuHighlight
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentColor = False
        ParentFont = False
      end
      object Button8: TButton
        Left = 239
        Top = 36
        Width = 83
        Height = 30
        Caption = #28165#31354
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = Button8Click
      end
      object Button6: TButton
        Left = 1
        Top = 36
        Width = 130
        Height = 30
        Caption = #29983#25104'GB2312'#24120#29992#23383#34920
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = Button6Click
      end
      object Button5: TButton
        Left = 2
        Top = 3
        Width = 129
        Height = 30
        Caption = #29983#25104'GB2312'#27721#23383#34920
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = Button5Click
      end
      object Button3: TButton
        Left = 132
        Top = 3
        Width = 107
        Height = 30
        BiDiMode = bdLeftToRight
        Caption = #28165#38500#33521#25991#21644#25968#23383
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentBiDiMode = False
        ParentFont = False
        TabOrder = 3
        OnClick = Button3Click
      end
      object Button2: TButton
        Left = 132
        Top = 36
        Width = 107
        Height = 30
        Caption = #28165#38500#37325#22797#30340
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = Button2Click
      end
      object Button9: TButton
        Left = 239
        Top = 3
        Width = 83
        Height = 30
        BiDiMode = bdLeftToRight
        Caption = #28165#38500#20013#25991#26631#28857
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ParentBiDiMode = False
        ParentFont = False
        TabOrder = 5
        OnClick = Button9Click
      end
      object Button10: TButton
        Left = 322
        Top = 3
        Width = 109
        Height = 30
        Caption = #31616#20307' -> '#32321#20307
        TabOrder = 6
        OnClick = Button10Click
      end
      object Button11: TButton
        Left = 323
        Top = 36
        Width = 109
        Height = 30
        Caption = #32321#20307' -> '#31616#20307
        TabOrder = 7
        OnClick = Button11Click
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 595
      Width = 439
      Height = 23
      Align = alBottom
      TabOrder = 2
      object left_bottom_txt: TLabel
        Left = 1
        Top = 1
        Width = 437
        Height = 21
        Align = alClient
      end
    end
  end
  object Panel2: TPanel
    Left = 444
    Top = 0
    Width = 562
    Height = 619
    Align = alClient
    TabOrder = 1
    object Memo2: TMemo
      Left = 1
      Top = 185
      Width = 560
      Height = 433
      Align = alClient
      Color = clMenuBar
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Fixedsys'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 0
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 560
      Height = 184
      Align = alTop
      TabOrder = 1
      object Image1: TImage
        Left = 2
        Top = 4
        Width = 255
        Height = 154
        Center = True
      end
      object Label6: TLabel
        Left = 264
        Top = 162
        Width = 288
        Height = 13
        AutoSize = False
        Caption = #27880#65306#20570#23436#21518#35831#37325#28857#26816#26597' _, g, y W, @ ,M '#31561#23383#31526#12290'             '
      end
      object Label7: TLabel
        Left = 5
        Top = 163
        Width = 97
        Height = 13
        AutoSize = False
        Caption = #39044#35272#65306
      end
      object GroupBox1: TGroupBox
        Left = 264
        Top = 0
        Width = 185
        Height = 138
        Caption = #35774#32622#65306
        TabOrder = 0
        object Label2: TLabel
          Left = 6
          Top = 19
          Width = 12
          Height = 13
          Caption = #23485
        end
        object Label3: TLabel
          Left = 101
          Top = 18
          Width = 12
          Height = 13
          Caption = #39640
        end
        object Label4: TLabel
          Left = 10
          Top = 46
          Width = 97
          Height = 13
          AutoSize = False
          Caption = #27700#24179#20559#31227':'
        end
        object Label5: TLabel
          Left = 11
          Top = 70
          Width = 97
          Height = 13
          AutoSize = False
          Caption = #22402#30452#20559#31227':'
        end
        object SpinEdit1: TSpinEdit
          Left = 24
          Top = 16
          Width = 57
          Height = 22
          MaxValue = 200
          MinValue = 1
          TabOrder = 0
          Value = 12
          OnChange = SpinEdit1Change
        end
        object SpinEdit2: TSpinEdit
          Left = 120
          Top = 14
          Width = 57
          Height = 22
          MaxValue = 200
          MinValue = 1
          TabOrder = 1
          Value = 12
          OnChange = SpinEdit2Change
        end
        object CheckBox2: TCheckBox
          Left = 13
          Top = 92
          Width = 139
          Height = 17
          Caption = #33258#21160#21152#19978'ASCII'#30721#34920
          Checked = True
          State = cbChecked
          TabOrder = 2
        end
        object CheckBox1: TCheckBox
          Left = 13
          Top = 114
          Width = 121
          Height = 17
          Caption = #23383#20307#25490#24207
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
        object Edit1: TEdit
          Left = 80
          Top = 44
          Width = 89
          Height = 21
          TabOrder = 4
          Text = '0'
          OnChange = Edit1Change
        end
        object Edit2: TEdit
          Left = 79
          Top = 67
          Width = 89
          Height = 21
          TabOrder = 5
          Text = '0'
          OnChange = Edit2Change
        end
      end
      object Button7: TButton
        Left = 452
        Top = 38
        Width = 97
        Height = 31
        Caption = 'Help'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = Button7Click
      end
      object Button4: TButton
        Left = 453
        Top = 105
        Width = 97
        Height = 31
        BiDiMode = bdLeftToRight
        Caption = #25335#36125#21040#21098#36148#26495
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentBiDiMode = False
        ParentFont = False
        TabOrder = 2
        OnClick = Button4Click
      end
      object Button1: TButton
        Left = 453
        Top = 72
        Width = 97
        Height = 31
        Caption = #24320#22987#36716#25442
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = Button1Click
      end
      object BitBtn1: TBitBtn
        Left = 451
        Top = 6
        Width = 97
        Height = 31
        Caption = #23383#20307#36873#25321
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = BitBtn1Click
      end
      object Edit3: TEdit
        Left = 73
        Top = 160
        Width = 89
        Height = 21
        TabOrder = 5
        OnChange = Edit3Change
      end
    end
  end
  object StatusPanel: TPanel
    Left = 304
    Top = 264
    Width = 345
    Height = 105
    TabOrder = 2
    Visible = False
    object Gauge1: TGauge
      Left = 24
      Top = 48
      Width = 297
      Height = 25
      Progress = 0
    end
    object StatusLabel: TLabel
      Left = 16
      Top = 24
      Width = 313
      Height = 13
      AutoSize = False
      Caption = #29366#24577
    end
  end
  object FontDialog1: TFontDialog
    Font.Charset = ANSI_CHARSET
    Font.Color = clNone
    Font.Height = -15
    Font.Name = #23435#20307
    Font.Style = []
    Device = fdBoth
    Options = [fdWysiwyg]
    Left = 424
    Top = 112
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 396
    Top = 112
  end
end
