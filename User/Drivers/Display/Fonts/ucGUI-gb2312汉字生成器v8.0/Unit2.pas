unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, ComCtrls, StdCtrls, Gauges;

type
  TForm2 = class(TForm)
    Label1: TLabel;
    Timer1: TTimer;
    Gauge1: TGauge;
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

uses Unit1;

{$R *.dfm}

procedure TForm2.Timer1Timer(Sender: TObject);
begin
  case form1.step of
  0:begin  end;
  1:begin label1.Caption:='������ȡ�ַ�����...'; end;
  2:begin label1.Caption:='�����Ż��ַ���...'; end;
  3:begin label1.Caption:='�������ɵ����ַ��ṹ��...'; end;
  4:begin label1.Caption:='�������ַ��ṹ��...'; end;
  5:begin label1.Caption:='��������������...'; end;
  6:begin close end;
  end;
  gauge1.Progress:=form1.progress;
end;

end.
