//查询游戏交费时间的命令，直接从数据库取数据，应该禁止频繁读取
//Write By JackyBoy@XAJH 2001/5/15
#include <ansi.h>

inherit F_CLEAN_UP;

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}
mapping channels;
string *chann;
string cmdhelp=
"选单命令格式：<"HIR"频道"HIG">   <"HIR"命令"HIG">\n"+
"其中频道为你可以设置和使用的频道的英文名，比如"HIC"chat"HIG","HIM"rumor"HIG"等\n"+
"而命令为"HIR"public"HIG","HIR"main"HIG"或者"HIR"none"HIG"，其中：\n"+
HIR"public"HIG"表示开启频道并将信息显示到公共信息窗口\n"+
HIR"main  "HIG"表示开启频道并将信息显示到主信息窗口中\n"+
HIR"none  "HIG"表示将频道关闭，不再接收频道信息\n"+
"你也可以输入"HIR"exit"HIG"退出命令选单，或输入"HIR"help/?"HIG"获取本信息！\n";

int do_chan(string,object,int);
int show_main(object);

int main(object me,string arg)
{
        channels=CHANNEL_D->query_chann();
        chann=keys(channels);
        //非巫师就过滤掉这些巫师频道设置
        if(!wizardp(me)) chann -= ({"wiz","sys","debug","nch"});
        chann -= ({"shout"});

        if(arg)
                return do_chan(arg,me,1);
        show_main(me);
        return 1;
}

int show_main(object me)
{
        class channel_class ch;
        string *tuned_ch;
        string s,str,state;

        ch = new(class channel_class);
        //tuned_ch=query("channels", me);
        tuned_ch = CHANNEL_D->query_using_channel(me, 1);

        str=me->name()+"的频道设置为：\n"HIC"≡"HIY"------------------------------------------------------------"HIC"≡\n"NOR;
        str+=sprintf(HIC" %-10s        %-8s         %-8s\n\n","频道命令","频道名称","频道状态");
        foreach(s in chann)
        {
                ch = copy(channels[s]);
                if( !pointerp(tuned_ch) || !sizeof(tuned_ch) ) state=HIG"关闭";
                else if(member_array(s,tuned_ch)==-1) state=GRN"关闭";
                else if( query("chann/"+s, me))state=HIC"主窗口";
                else state=HIY"公共窗口";
                str+=sprintf(WHT"[%-10s]       [%-8s]        %-8s\n",s,ch->msg,state);
        }
        str+="\n"HIC"≡"HIY"------------------------------------------------------------"HIC"≡\n"NOR;
        str+="请输入命令("HIY"help"NOR"看帮助，"HIY"exit"NOR"退出)：";
        write(str);
        input_to( (: do_chan :) ,me);
        return 1;
}


void open_ch(object me,string arg)
{
        class channel_class ch;
        mapping channels = fetch_variable("channels", get_object(CHANNEL_D));
        int my_channels = query("channels", me);

        if( undefinedp(ch = channels[arg]) || !classp(ch) )
                return;

        set("channels", my_channels | ch->number, me);
        CHANNEL_D->register_channel(me, ch->number);
}

int do_chan(string arg,object me,int once)
{
        string ch,cmd;
        int tmp;

        if(!arg)
        {
                write("\n请输入命令("HIY"help"NOR"看帮助，"HIY"exit"NOR"退出)：");
                input_to( (: do_chan :) ,me);
                return 1;
        }
        arg=lower_case(arg);
        arg=me->remove_leading_space(arg);
        while(strsrch(arg,"  ")!=-1) arg=replace_string(arg,"  "," ");
        switch(arg)
        {
                case "?":
                case "help":
                        //显示帮助信息
                        write(HIG+cmdhelp+NOR);
                        break;
                case "q":
                case "quit":
                case "exit":
                        write(HIG"退出频道设置程序。。。\n"NOR);
                        once=1;break;
                default:
                        //进行程序处理
                        tmp=0;
                        if(sscanf(arg,"%s %s",ch,cmd)==2)
                        {
                                switch(cmd)
                                {
                                        case "public":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        open_ch(me,ch);
                                                        delete("chann/"+ch, me);
                                                        write(HIG"你打开了" + channels[ch]["name"] + "频道。\n"NOR);
                                                }
                                                else write(HIG"频道错误！没有"+HIY+"ch"+HIG+"这个频道！\n"NOR);
                                                break;
                                        case "main":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        open_ch(me,ch);
                                                        set("chann/"+ch, 1, me);
                                                        write(HIG"你打开了" + channels[ch]["name"] + "频道。\n"NOR);
                                                }
                                                else write(HIG"频道错误！没有"+HIY+"ch"+HIG+"这个频道！\n"NOR);
                                                break;
                                        case "none":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        set("channels",query("channels",  me)-({ch}), me);
                                                        write(HIG"你关闭了" + channels[ch]["name"] + "频道。\n"NOR);
                                                }
                                                else write(HIG"频道错误！没有"+HIY+"ch"+HIG+"这个频道！\n"NOR);
                                                break;
                                        default:
                                                tmp=1;
                                }
                        }
                        else tmp=1;
                        if(tmp)
                                write(HIG+cmdhelp+NOR);
        }
        if(!once) show_main(me);
        return 1;
}

int help()
{
        write(@HELP
指令格式 : chann                         (菜单模式)
           chann    <命令串>             (直接指定)

这个指令可以让你自由设置频道信息的显示，关闭或者显示位置。
显示位置有main（主窗口）和public（公共信息窗口）两个选择。
如果位置设置为没有（none），则表示要关闭该频道。

命令串格式为：<频道> < main | public | none>
频道为你要进行操作的频道名称，后面跟着的是none表示要关闭该
频道，跟着main表示要打开频道并将信息显示在主区域窗口，如果
是public则显示到公共信息区域窗口。

直接指定的命令模式例子：
chann chat none    —— 此操作为将chat频道关闭
chann chat main    —— 此操作将打开chat频道并显示到主窗口
chann rumor public —— 此操作将在公共窗口打开rumor频道
HELP );
    return 1;
}
