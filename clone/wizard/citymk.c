
/*
 * 物件： 城市精灵(City Maker) V1.0
 * 作者： 冰河 (Glacier@［雪域．黑潮］)
 * 日期： 2001/01/11
 * 备注： ES_Base_Code
 * 修改： 功能模块修改成向导方式，加入地图档错误判断。
 *        任何时候输入点 "."，都可以放弃编辑。
 *                            Glacier -- 2001.2.20
 *
 * 修改： 加入自己设定文件名功能。文件名导出格式为：城市名_房间名.c
 *        其中城市名为地图文件的名称，房间名在地图文件第一行设定。
 *                            Lonely -- 2001.3.12
 */
// #pragma save_binary
inherit ITEM;
inherit F_AUTOLOAD;

#include <mudlib.h>
//#define _check_map
#define _show_map

mixed maps, icons, icons1;
mapping room_short = ([]),room_filename = ([]);
string city,current_path;
string *outdoors_room;
string outdoors;
int _Mrow, _Mcol, _size;
int set_path(string arg);
int set_outdoors_room(string arg);
int save_file(string yn, string file_name, string file);
int confirm_make(string yn);
void create()
{
        set_name("城市精灵 V1.1", ({ "citymaker", "maker" }) );
        set_weight(2000);
        set("unit", "个" );
        set("long", @LONG
    这个是一个方便巫师工作的工具，可以快速建立完整的区域结构。
请使用 help citymaker 获得详细帮助。
LONG
        );
        setup();
}

void init()
{
        if( wizardp(environment()) ) {
                seteuid(getuid(environment()));
                add_action("do_makecity", "make");
                add_action("do_help", "help");
        }
}

int process_map(string file)
{
        string input,*line;
        int i,j,v;
        int _Trow, _Tcol;
        if(file_size(file)>0)
        {
            input=read_file(file);
//处理 line
            line=explode(input,"\n");
            icons1=explode(line[0]," ");
            for(i=0;i<sizeof(icons1);i++)
            {
                j=i+1;
                if (strsrch(icons1[i],"\t")!=-1 || strsrch(icons1[i],".")==-1)
                {
                write("[ Citymaker ]：房间标识位错误，请检查地图第一行标识位[ "+ j +" == "+icons1[i]+" ]处。\n");
                write("[ Citymaker ]：含有制表符或者<房间标识.房间名称>之间不含分割符\".\"。\n");
                return 0;
                }
            }
            icons=allocate(sizeof(icons1));
            for(i=0;i<sizeof(icons1);i++)
            {
                //icons[i]=allocate(2);
                icons[i]=allocate(3);
                icons[i]=explode(icons1[i],".");
            }
            for(i=0;i<sizeof(icons1);i++)
            {
                room_short[icons[i][0]] = icons[i][1];
                room_filename[icons[i][0]] = icons[i][2];
            }
//处理 mapping room_short
            _Trow=sizeof(line);
            _Mrow=_Trow-1;
            _size=_Trow;
            for(i=1;i<(sizeof(line));i++)
            {
                _Tcol=sizeof(line[i]);
                if (_Mcol<_Tcol) {_Mcol=_Tcol;}
            }
            if (_size<_Mcol) {_size=_Mcol;}
//处理成矩阵
            for(i=1;i<(sizeof(line));i++)
            {
                j=i+1;
                if (strsrch(line[i],"\t")!=-1)
                {
                write("[ Citymaker ]：房间标识位错误，请检查地图第["+j+"]行[ "+line[i]+" ]处。\n");
                write("[ Citymaker ]：含有制表符。\n");
                return 0;
                }
                for (_Tcol=sizeof(line[i]);_Tcol<_Mcol;_Tcol++)
                 {
                        line[i]+= " " ;
                 }
            }
                maps = allocate(_size);
//处理 maps
                for(v=1;v<(sizeof(line));v++)
            {
            maps[v-1]=allocate(_size);
            maps[v-1]=explode(line[v],"");
            }
            return 1;
        } else return 0;
}



int makeroom(int _row, int _col)
{
        int i;
        string file_name,file,*exit_key,room;
        mapping exit=([]);
        room=maps[_row][_col];
                write("[ Citymaker ]：room("+_row+","+_col+") == "+room+" ");
  if (_row>1)                       {if (maps[_row-1][_col] == "|"   && maps[_row-2][_col]!=" ")     {exit["north"]=room_filename[maps[_row-2][_col]];}}
  if (_row>1 && _col<_Mcol-1)       {if (maps[_row-1][_col+1] == "/" && maps[_row-2][_col+2]!=" ")   {exit["northeast"]=room_filename[maps[_row-2][_col+2]];}}
  if (_col<_Mcol-1)                 {if (maps[_row][_col+1] == "-"   && maps[_row][_col+2]!=" ")     {exit["east"]=room_filename[maps[_row][_col+2]];}}
  if (_row<_Mrow-1 && _col<_Mcol-1) {if (maps[_row+1][_col+1] == "\\"&& maps[_row+2][_col+2]!=" ")   {exit["southeast"]=room_filename[maps[_row+2][_col+2]];}}
  if (_row<_Mrow-1)                 {if (maps[_row+1][_col] == "|"   && maps[_row+2][_col]!=" ")     {exit["south"]=room_filename[maps[_row+2][_col]];}}
  if (_row<_Mrow-1 && _col>1)       {if (maps[_row+1][_col-1] == "/" && maps[_row+2][_col-2]!=" ")   {exit["southwest"]=room_filename[maps[_row+2][_col-2]];}}
  if (_col>1)                       {if (maps[_row][_col-1] == "-"   && maps[_row][_col-2]!=" ")      {exit["west"]=room_filename[maps[_row][_col-2]];}}
  if (_row>1 && _col>1)             {if (maps[_row-1][_col-1] == "\\"&& maps[_row-2][_col-2]!=" ")   {exit["northwest"]=room_filename[maps[_row-2][_col-2]];}}
  //file_name=current_path++"_"+room_filename[maps[_row][_col]]+".c";
  file_name=current_path+room_filename[maps[_row][_col]]+".c";
  file=sprintf("/*\n * 文件    : %s (%s)\n",room_short[maps[_row][_col]],room_filename[maps[_row][_col]]);
        file+=sprintf(" * 作者    : %s(%s@%s)\n * 创建    : %s\n",this_player()->query("name"),this_player()->query("id"),MUD_NAME,ctime(time()));
        file+=@FILE_HEAD
 * 工具    : Build with Citymaker@Glacier
 * 修改    : Changed By Lonely@泥潭
 */
#include <ansi.h>
inherit ROOM;
void create()
{
FILE_HEAD
;
        file+=sprintf("\tset(\"short\", \"%s\");\n",room_short[maps[_row][_col]]);
file+=@FILE_LONG
        set("long", @LONG
夜.泊.秦.淮.居.谁.家？

LONG
);
        set("objects",([
        ]));
        set("exits",([
FILE_LONG;
;
        exit_key=keys(exit);
        for(i=0;i<sizeof(exit_key);i++) {
                file=sprintf("%s\t\"%s\" : __DIR__\"%s\",\n",file,exit_key[i],exit[exit_key[i]]);
        }
        file+=@FILE_2
        ]));
FILE_2
;
  if (member_array(lower_case(maps[_row][_col]),outdoors_room)==-1 )
{
        file+=@FILE_3
        setup();
//      replace_program(ROOM);
}
FILE_3
;
}
else {
        file+=sprintf("\tset(\"outdoors\",\"%s\");\n",city);
        file+=@FILE_3
        setup();
//      replace_program(ROOM);
}
FILE_3
;
}

return save_file("y", file_name, file);
}

int do_makecity(string arg)
{
        int _row,_col;
        string file,room;
        if (!arg) return notify_fail ("[ Citymaker ]：makecity <地图档案名>\n");
        if (strsrch(arg,".")!=-1 || strsrch(arg," ")!=-1)
        {
        write("[ Citymaker ]：错误地图档名，地图档中不允许出现\".\"或者\" \"，\n ");
        write("              请直接使用你想建立的城市名为地图档名。\n");
        return 1;
        }
        else
        {

                //city=;
                file=resolve_path(this_player()->query("cwd"), arg);
                if(process_map(file))
                {
                        write("[ Citymaker ]：正在载入地图档[ "+file+" ]...\n");
#ifdef _check_map
                        for(_row=0;_row<sizeof(maps);_row++)
                        {
                                for(_col=0;_col<sizeof(maps[_row]);_col++)
                                {
                                room=maps[_row][_col];
                                write("room("+_row+","+_col+") == "+room + "\n");
                                }
                        }
#endif
#ifdef _show_map
                        for(_row=0;_row<sizeof(maps);_row++)
                        {
                                for(_col=0;_col<sizeof(maps[_row]);_col++)
                                {
                                room=maps[_row][_col];
                                write(""+room + "");
                                }
                         write("\n");
                        }
                        write("[ Citymaker ]：_Mrow = "+_Mrow+" _Mcol = "+_Mcol+"\n");
#endif
                        write("[ Citymaker ]：地图档[ "+file+" ]载入完成!!\n");
                }
                else
                {
                        return notify_fail("[ Citymaker ]：地图档[ "+file+" ]载入失败。\n");
                }
        }
          write("[ Citymaker ]：请设定存储档案目录(默认为当前目录)：");
          input_to ( "set_path" );

        return 1;
}

int save_file(string yn, string file_name, string file)
{
        if( strlen(yn)<1 || yn[0]!='y' ) return 1;

      if(file_name[0..2]!="/u/") return 0;
//只允许在/u/目录下面建立文件
        rm(file_name);
        write(" 建立 " + file_name + "....");

        if( write_file(file_name, file,1)==1 ) {
                write("OK!\n");
                return 1;
        } else
                write("你没有写入这个档案(" + file_name + ")的权利。\n");
                return 0;
}

int set_path(string arg)
{
        string dir;
        if (arg == ".") { write ("[ Citymaker ]：放弃本次操作。\n"); return 1; }
        if (strsrch(arg," ")!=-1)
        {
        write("[ Citymaker ]：错误的路径，请设定存储档案目录(默认为当前目录)：");
        input_to ( "set_path" );
        return 1;
        }
        if(!arg)
        {
                if(dir = this_player()->query("cwd"))
                {
                        current_path=dir;
                        write("[ Citymaker ]：自动设定存储档案目录为当前目录[ "+current_path+" ]。\n");
                        write("[ Citymaker ]：请设定户外房间类型(例如：c,g 则地图为 c、g 的房间将被设定为户外)：");
                        input_to("set_outdoors_room");
                        return 1;
                } else return notify_fail("[ Citymaker ]：无法自动设定目录，放弃操作。\n");
        }
        else
        {
                dir = resolve_path(this_player()->query("cwd"), arg);
                if(file_size(dir)!=-2) { write("[ Citymaker ]：没有这个目录，放弃操作。\n"); return 1; }
                if(dir[strlen(dir)-1]!='/') dir += "/";
                current_path=dir;
                write("[ Citymaker ]：设定存储档案目录为[ "+current_path+" ]。\n");
                write("[ Citymaker ]：请设定户外房间类型(例如：c,g 则地图为 c、g 的房间将被设定为户外)：");
                input_to("set_outdoors_room");
        }
                return 1;
}
int set_outdoors_room(string arg)
{
        int  i;
        string *tmp,test,argt;
        argt=lower_case(arg);
        if (arg == ".") { write ("[ Citymaker ]：放弃本次操作。\n"); return 1; }
        if (strsrch(argt," ")!=-1 )
        {
        write("[ Citymaker ]：户外房间类型设定错误，不允许出现\" \"。\n");
        write("[ Citymaker ]：请设定户外房间类型(例如：c,g 则地图为 c、g 的房间将被设定为户外)：");
        input_to ( "set_outdoors_room" );
        return 1;
        }
        tmp=(explode(lower_case(arg),","));
        for (i=0;i<sizeof(tmp);i++)
        {
        test=tmp[i];
        if (strlen(test)>1) {
                write("[ Citymaker ]：户外房间设定错误，房间标识长度应为单个字符。\n");
                write("[ Citymaker ]：请设定户外房间类型(例如：c,g 则地图为 c、g 的房间将被设定为户外)：");
                input_to ( "set_outdoors_room" );
                return 1;
                }
        }
        if(!arg)
        {
        write ("[ Citymaker ]：设定所有房间为户外...OK。\n");
        }
        outdoors_room=(explode(lower_case(arg),","));
        for (i=0;i<sizeof(outdoors_room);i++)
        {
        outdoors=outdoors_room[i];
        write("[ Citymaker ]：设定房间[ "+outdoors+" ]为户外...OK。\n");
        }
        write("[ Citymaker ]：设定完成，Citymaker 将会生成城市档案，请确认(y/n)：");
        input_to("confirm_make");
        return 1;
}
int confirm_make(string arg)
{
        int  _row,_col;
        int count=0;
        if( arg=="" )
        {
        write("[ Citymaker ]：需要确认，您确定吗(y/n)？");
        input_to("confirm_make");
        return 1;
        }
        if( arg[0]!='y' && arg[0]!='Y' ) {write ("[ Citymaker ]：放弃本次操作。\n"); return 1;}
        write("[ Citymaker ]：正在建立城市 ... ...\n");
        for(_row=0;_row<sizeof(maps);_row++)
        {
        for(_col=0;_col<sizeof(maps[_row]);_col++)
        {
                if (maps[_row][_col]!=" "
                 && maps[_row][_col]!="|"
                 && maps[_row][_col]!="/"
                 && maps[_row][_col]!="\\"
                 && maps[_row][_col]!="-" )
                {
                        makeroom(_row,_col);
                        count++;
                }
                }
        }
        write("[ Citymaker ]：操作报告，共计[ " + count +" ]个房间！\n");
        return 1;
}

int do_help(string arg)
{
        if(arg=="citymaker" ||arg== "maker")
        {
                write(@HELP_LONG
城市精灵 V1.1 ( 2001.2)            - By Glacier@［雪域．黑潮］
                                     Email:wizard@game.com.cn

这个是一个为方便巫师工作的城市工具，可以快速建立完整的区域结构。

1.编辑地图档, 范例如下：
-----------------------------------------------------------------
a.客房.kefang b.厢房.xiangfang c.走廊.zoulang d.大厅.dating
e.厨房.chufang f.花园.huayuan g.大门.damen h.内室.neishi
(注意：上两行应合并为一行，由于过宽，为了便于显示，所以在这里分为两行)
  g   b
  |  / \
b-c-b   b
  |  \ /
a-d-a b
  |
h-f-e
------------------------------------------------------------------
地图说明：   本地图档所加边框(---)，为解释地图所用，实际地图中没有。
             地图第一行为图例，采用<房间标识.房间名称.房间文件名>的
             方式，即a代表客房，地图中所有a均被处理成客房。 房间标
             识、房间名称和房间文件名之间用＂.＂分割。
             用＂-、\、/、|＂来表示常用的的八中通路(不考虑地形)即：
             west、east、northwest、southeast、northeast、southwest
             north、south。
注意事项：   所有房间均应在第一行有图例说明，否则将无法正常生成房间。
             地图中所有字符均为半角字符，只允许出现空格＂ ＂，不允许
             出现制表符 \t 。为避免出错请严格按造本地图档建立。
2. 指令格式：make <地图档>  ( 最好把城市名作为地图档名称， 这是因为
             Citymaker 在设置outdoors房间的时候使用地图档名作为房间
             的所属城市。)
3. Citymaker 需要设定存放档案的路径： <目录名> (默认为当前所在目录)。
4. Citymaker 需要设定户外的房间：<户外房间标识,户外房间标识,...
             所设定的房间将被设定为户外(默认为室内)。
5. 如果以上设定无误，确认后 Citymaker 会批量生成城市档案。(确认后本?             序将直接改写重名文件，所以请注意你所者设置的存储目录。
6. 本程序欢迎修改，但请保留原作者名。

HELP_LONG);
                return 1;
        }
        return 0;
}

string query_autoload() { return "";}

void autoload(string param)
{return ;}
