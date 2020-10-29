//help.c,具有部分bbs和超强的文件链接功能
//created by hyee，看到Host的help系统受到启发
//不同的mudlib请注意修正define的目录和valid_write()
//2001.1.30 change by xkiller@ldj.ciom
#include <mudlib.h>
#include <ansi.h>
#include <login.h>
/*定义其他文档的所在目录*/
#define DIR "/help/"
/*定义本文件的存档所在的目录*/
#define POST DIR"mudbbs.o"
/*定义玩家register文件所在目录*/
#define REGISTER DIR+"register/"
/*定义各种留言板所在目录*/
#define BOARD "/clone/board/"
/*board的主存文件*/
#define BOARDCENTER BOARD+"center.h"
/*定义能对本系统进行修改的巫师等级*/
#define WIZLEVEL "(wizard)"
inherit ITEM;
inherit F_SAVE;
varargs void display(object ob);
void auto_load();
void view_main();
void view_main_1();
void m_display();
void u_display();
void view6();
void view7(string arg);
void do_discard(object ob);
void do_more(string arg,string *text,int line,object ob);
void getname1(string arg);
void getname3(string arg);
void getname2(string str,string arg);
void delfile(string arg);
protected void confirm_main_choice(string arg);
protected void confirm_p_choice(string arg,object ob);
protected void confirm_k_choice(string arg);
protected void confirm_l_choice(string arg);
protected void confirm_choice(string arg);
protected void a(string arg, string register);
protected void b(string arg, string register);
protected void c(string arg, string register);
protected void d(string arg, string register);
protected void e(string arg, string register);
protected void f(string arg, string register);
protected void g(string arg, string register);
protected void y(string arg, string register);
protected void confirm_u_choice(string arg);
string age_string(int time);
int do_post(string arg,object ob);
int wizlist();
int message();
int message1();
string query_save_file()
{
        return POST;
}
void create()
{
        seteuid(getuid());
        set("name","泥潭·江湖论坛");
        mkdir(DIR);
        mkdir(REGISTER);
        restore();
        rm(BOARDCENTER);
        save();
}

int start_help(string msg,object ob)
{
        if(!ob) ob=this_object();
        do_more("d",explode(msg, "\n"),0,ob);
}

int main(object me, string arg)
{
        int i;
        string file, *search;

        seteuid(getuid());
        set_temp("help", 1, me);
        m_display();
        write(YEL"你将要选择："NOR);
        input_to((:confirm_main_choice:),this_player());
        return 1;
}

void view_main()
{
     object me;
     string name,select;
     me = this_player();
     select=query_temp("select", me);
     write(CLR"\n");
     if(select== "main") name = "主选单";
     else if( select== "intro") name = "游戏概况";
     else if( select== "news") name = "泥潭新闻";
     else if( select== "map") name = "泥潭地图";
     else if( select== "family" ) name="门派介绍";
     else if( select== "skills" ) name="武功介绍";
     else if( select== "user") name = "个人设定";
     else if( select== "board") name = "论坛精华";
     else if( select== "post") name = "灌水天地";
     else if( select== "other" ) name="其他内容";
     else if( select== "xyz" ) name="好好学习";
     write(HIY"分类选单"HIC"                     【"HIY+MUD_NAME+HIC"江湖论坛】            "HIY"选单["+select+"]\n"NOR);
     write("目前选择：[ "+HIG+name+NOR+" ]\n");
     write(HIR"□－－－－－－－－－－－－－－┤ 公告版 ├－－－－－－－－－－－－－－□\n"NOR);
     auto_load();
     write(HIR"□－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－□\n"NOR);
     write(CYN"                       【请您使用首字母选择进入】\n"NOR);
}
void view_main_1()
{
     int i,ppl_cnt,wiz_cnt;
     object *usr;
     usr = users();
     ppl_cnt=0;
     for(i=0; i<sizeof(usr); i++)
       {
              if( wizardp(usr[i]) ) wiz_cnt++;
          ppl_cnt++;
       }
     if (!wizardp(this_player())) ppl_cnt = ppl_cnt - wiz_cnt;
     write(HIY"_.-*```*-.__.-*```*-.__.-*```*-.__.-*```*-.__.-*```*-.__.-*```*-.__.-*\n"NOR);
     write(YEL"现在时间:["CYN""+ctime(time())+""YEL"]    在线玩家：["CYN""+ppl_cnt+""YEL"]  目前权限:["CYN""+wizhood(this_player())+""YEL"]\n"NOR,);
}
void view_main_k()
{
     object me;
     string name,select;
     me = this_player();
     select=query_temp("select", me);
     write(CLR"\n");
     if(select== "main") name = "主选单";
     else if( select== "intro") name = "游戏概况";
     else if( select== "news") name = "泥潭新闻";
     else if( select== "map") name = "泥潭地图";
     else if( select== "family" ) name="门派介绍";
     else if( select== "skills" ) name="武功介绍";
     else if( select== "user") name = "个人设定";
     else if( select== "board") name = "论坛精华";
     else if( select== "post") name = "灌水天地";
     else if( select== "other" ) name="其他内容";
     else if( select== "xyz" ) name="好好学习";
     write(YEL"分类选单"WHT"                         【"+MUD_NAME+"】                  "YEL"选单["+select+"]\n"NOR);
     write("目前选择：[ "+HIG+name+NOR+" ]\n");
     write(RED"□－－－－－－－－－－－－－－┤ 公告版 ├－－－－－－－－－－－－－－□\n"NOR);
}
void m_display()
 {
     set_temp("select", "main", this_player());
     view_main();
     write("                        "BRED+HIG"(I)"NOR"ntro   〖  游戏概况  〗\n");
     write("                        "BRED+HIG"(M)"NOR"ap     〖  泥潭地图  〗\n");
     write("                        "BRED+HIG"(F)"NOR"amily  〖  门派介绍  〗\n");
//     write("                        "BRED+HIG"(S)"NOR"kills  〖  武功介绍  〗\n");
     write("                        "BRED+HIG"(N)"NOR"ews    〖  泥潭新闻  〗\n");
     write("                        "BRED+HIG"(O)"NOR"ther   〖  其他内容  〗\n");
     write("                        "BRED+HIG"(B)"NOR"oard   〖  论坛精华  〗\n");
     write("                        "BRED+HIG"(X)"NOR"yz     〖  好好学习  〗\n");
     write("                        "BRED+HIG"(P)"NOR"ost    〖  灌水天地  〗\n");
     write("                        "BRED+HIG"(U)"NOR"ser    〖  个人设定  〗\n");
     write("                        "BRED+HIG"(G)"NOR"oodbye 【  "HIM"回到江湖"NOR"  】\n");
     view_main_1();
}

void auto_load()
{
/*
    if(random(10) > 5)
        wizlist();
*/
    if( random(20) >  10)
        message();
    else
        message1();
}

int message1()
{
      object me;
      int i;
      me = this_player();
      i=query("combat/MKS", me)+query("combat/PKS", me);
      write(HIM"      亲爱的"HIR+me->name()+HIM"啊, 您在【泥潭】的江湖中已经摸爬滚打了"+age_string(query("mud_age",me))+"耶!!\n");
      write(HIM"在您在本泥巴的分分秒秒中,您已经累积了"+chinese_number(query("combat_exp", me))+"点的江湖经验\n");
      write(HIM"      共击倒"+chinese_number(i)+"个对手\n");
      write(CYN"                        加油喔!!addoil!! \n");
}
string age_string(int time)
{
        int month, day, hour, min, sec;
        sec = time % 60;
        time /= 60;
        min = time % 60;
        time /= 60;
        hour = time % 24;
        time /= 24;
        day = time % 30;
        month = time / 30;
        return (month?month + "月":"") + (day?day + "天":"") +
        (hour?hour + "小时":"") + min + "分";
}

int message()
{
 write(WHT"   ●    （ ● ）  （●）      ●）     ●     （●）   □●□   （●\n"NOR);
 write(WHT" ＜｜＞   └｜┘    （（（   （｜     （｜）   　｜）     ｜      （□\n"NOR);
 write(WHT"  ／＼    ＜  □   （         ／ ）    （□     （ ＼   □  □    ＜））\n"NOR);
 write(HIC""HIR+this_player()->name()+HIC",千万别挖泥太久喽，注意劳逸结合。迈步如婴之炯然，蓄势如日之初升。\n"NOR);
}

int wizlist()
{
        string *wizlist;
        string *list;
        string wiz_name,wiz_level,str,str1,str2,str3,str4,str5;
        int i,s1,s2,s3,s4,s5;
        str1=str2=str3=str4=str5="";
        s1=s2=s3=s4=s5=0;

        list = sort_array(SECURITY_D->query_wizlist(),1);
        wizlist = explode(read_file(WIZLIST), "\n");
        for(i=0; i<sizeof(wizlist); i++)
        {
            sscanf(wizlist[i], "%s %s", wiz_name, wiz_level);
            switch(wiz_level)
            {
                case "(immortal)":
                        str1 += (s1?"\t":"")+wiz_name;
                        s1++;
                        if(s1%3==0) str1 += "\n \t\t ";
                        break;
                case "(apprentice)":
                        str2 += (s2?"\t":"")+wiz_name;
                        s2++;
                        if(s2%3==0) str2 += "\n \t\t ";
                        break;
                case "(wizard)":
                        str3 += (s3?"\t":"")+wiz_name;
                        s3++;
                        if(s3%3==0) str3 += "\n \t\t ";
                        break;
                case "(arch)":
                        str4 += (s4?"\t":"")+wiz_name;
                        s4++;
                        if(s4%3==0) str4 += "\n \t\t ";
                        break;
                case "(admin)":
                        str5 += (s5?"\t":"")+wiz_name;
                        s5++;
                        if(s5%3==0) str5 += "\n \t\t";
                        break;
            }
        }
        write(HIG"           【 仙人 】: "NOR+str1+"\n");
        write(HIB"           【 学徒 】: "NOR+str2+"\n");
        write(HIC"           【 巫师 】: "NOR+str3+"\n");
        write(HIY"           【 大巫师 】: "NOR+str4+"\n");
        write(HIW"           【 天神 】: "NOR+str5+"\n");
}

protected void confirm_main_choice(string arg)
{
        delete_temp("memer", this_player());
         switch(arg[0]){
                 case 'p':
                case 'P':
                        set_temp("select", "post", this_player());
                        set_temp("memer", "post/page", this_player());
                         display();
                     return ;
                     break;
                     case 's':
                case 'S':
                     set_temp("select", "skill", this_player());
                     display();
                     return;
                     break;
                     case 'i':
                     case 'I':
                     set_temp("select", "intro", this_player());
                     display();
                     return;
                     break;
                     case 'm':
                     case 'M':
                     set_temp("select", "map", this_player());
                     display();
                     return;
                     break;
                     case 'n':
                     case 'N':
                     set_temp("select", "news", this_player());
                     display();
                     return;
                     break;
                     case 'o':
                     case 'O':
                     set_temp("select", "other", this_player());
                     display();
                     return;
                     break;
                     case 'b':
                     case 'B':
                     set_temp("select", "board", this_player());
                     display();
                     return;
                     break;
                     case 'f':
                     case 'F':
                     set_temp("select", "family", this_player());
                     display();
                     return;
                     break;
                     case 'x':
                     case 'X':
                     set_temp("select", "xyz", this_player());
                     display();
                     return;
                     break;
                     case 'u':
                     case 'U':
                     set_temp("select", "user", this_player());
                     u_display();
                     write(YEL"\r请输入您的选择:"NOR);
                     input_to((:confirm_u_choice:),this_player());
                     return;
                     break;
                    case 'g':
                     delete_temp("select", this_player());
                     delete_temp("help", this_player());
                     return;
        }
        m_display();
        write(YEL"请输入您的选择:"NOR);
        input_to((:confirm_main_choice:),this_player());
          return;
}
/*留言板程序*/
void view1()
{
        write(CYN"  (P)"NOR"发表 "CYN"(D)"NOR"删除 "CYN"(U)"NOR"上翻 "CYN"(O)"NOR"下翻"
        CYN" (B)"NOR"返回 "CYN"(E)"NOR"读取 "CYN"(K)"NOR"上移 "CYN"(J)"NOR"下移\n");
        write(RED"□－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－□\n"NOR);
        return;
}
string view_msg(int flag,object ob)
{
        object me=this_player();
        string memer=query_temp("memer", me);
        mapping*notes=query("notes", ob);
        string file;
        int i,k,b,f;
        file="";
        k=sizeof(notes)-1;
        if(!sizeof(notes)) return "目前没有任何留言。\n";
        if(flag<0) flag=k;
        if(flag>k) flag=0;
        set(memer, flag, me);
        b=flag-7;f=flag+7;
        if(b<0) {f=f-b;b=0;}
        if(f>k) {b=b-f+k;f=k;}
        if(b<0) b=0;
        if(f>k) f=k;
        f++;
        for(i=b;i<f;i++)
        file += sprintf("%s["NOR+WHT +BRED"%3d"NOR"%s]  %-30s %12s (%s)(%s)\n"NOR,
                        (i==flag)?BRED +WHT:"",
                        i+1, (i==flag)?BRED +WHT:"",notes[i]["title"], notes[i]["author"],
                        notes[i]["authorid"],ctime(notes[i]["time"])[0..15] );
        return file;
}

protected void confirm_p_choice(string arg,object ob)
{
        object me=this_player();
        int k=atoi(arg);
        int p,num;
        string memer=query_temp("memer", me);
        mapping *notes;
        if(k>0)
        {
                set(memer, k-1, me);
                     display(ob);
             }
             switch(arg)
             {
                     case "p":
                     case "P":
                        if( time()-query("postover", this_player())<900 &&
                            !wizardp(this_player(1)))
                        {
                                write("你已经在不久前留言了，请稍等一会才继续留言。\n");
                                display(ob);
                                return;
                        }
                             do_post(0,ob);
                             return;
                             break;
                     case "b":
                     case "B":
                        if( query_temp("select", this_player()) == "board" )
                        {
                                confirm_main_choice("board");
                                return;
                        }
                             main(this_player(),0);
                             return;
                     case "j":
                     case "J":
                             set(memer,query(memer,  me)+1, me);
                             display(ob);
                             return;
                             break;
                     case "k":
                     case "K":
                             set(memer,query(memer,  me)-1, me);
                             display(ob);
                        return;
                             break;
                     case "u":
                     case "U":
                             set(memer,query(memer,  me)-15, me);
                             display(ob);
                             return;
                             break;
                     case "o":
                     case "O":
                             set(memer,query(memer,  me)+15, me);
                             display(ob);
                             return;
                             break;
                     case "d":
                     case "D":
                             do_discard(ob);
                             display(ob);
                             return;
                             break;
                     case "e":
                     case "E":
                             num=query(memer, this_player());
                        notes=query("notes", ob);
                        if( !pointerp(notes) || !sizeof(notes) )
                        {
                                write("留言板上目前没有任何留言。\n");
                                display(ob);
                                return;
                        }
                        if(  num+1 > sizeof(notes) )
                        {
                                write("没有这张留言。\n");
                                display(ob);
                                return;
                        }
                        printf("["BBLU"%3d"NOR"] %-30s %s(%s)(%s)\n",
                        num + 1, notes[num]["title"], notes[num]["author"], notes[num]["authorid"],
                        ctime(notes[num]["time"])[0..9]);
                             start_help(notes[num]["msg"],ob);
                             return;
                             break;
             }
             display(ob);
             return;
}
int edi(function callback)
{
        write(CYN"    书写结束用'.'，取消输入用 '^q'，使用内建列编辑器用 '^e'。\n"NOR);
        write(GRN"------－－－－－－－－－－－－－－－－－－－－－－－－－－－－－--\n│"NOR);
        input_to("input_lines", "", callback);
        return 1;
}

void input_lines(string line, string text, function callback)
{
        if( line=="." ) {
                write(GRN"------－－－－－－－－－－－－－－－－－－－－－－－－－－－－－--\n"NOR);
                (*callback)(text);
                return;
        } else if( line=="^q" ) {
                write("输入取消。\n");
                main(this_player(),0);
        } else if( line=="^e" ) {
        } else  {
                line=replace_string(line,";",";\n");
                text += line + "\n";
        }
        write(GRN"│"NOR);
        input_to("input_lines", text, callback);
}
void done_post(mapping note,object ob,string text)
{
        mapping *notes;
        if(strlen(text)<20)
        {
                write(CYN"本文被认为是灌水文章，不予发表。\n"NOR);
                display(ob);
                return;
        }
        text=replace_string(text,";","\n");
        note["msg"] = text;
        notes=query("notes", ob);
        if( !pointerp(notes) || !sizeof(notes) )
                notes = ({ note });
        else
                notes += ({ note });
        set("notes", notes, ob);
        write("留言完毕。\n");
        ob->save();
        set("postover", time(), this_player());
        display(ob);
        return;
}
int do_post(string arg,object ob)
{
        mapping note;
        if(!arg||arg=="")
        {
                write(YEL"\n请指定一个标题:"NOR"(“Q”键取消)");
                input_to((:do_post:),ob);
                return 1;
        }
        if(arg=="q"||arg=="Q")
        {
                display(ob);
                return 1;
        }
        note = allocate_mapping(5);
        note["title"] = arg;
        note["author"] = this_player()->name(1);
        note["authorid"]=query("id", this_player());
        note["time"] = time();
        edi((: done_post,note,ob:));
        // this_player()->edit((: done_post,note,ob:));
             return 1;
}
void do_discard(object ob)
{
        mapping note,*notes;
        int num;
        string memer=query_temp("memer", this_player());
        num=query(memer, this_player())+1;
        notes=query("notes", ob);

        if( !arrayp(notes) ||!sizeof(notes)||num < 1 || num > sizeof(notes))
        {
                write("没有这张留言。\n");
                return;
        }
        num--;
        if( notes[num]["authorid"] != query("id", this_player(1) )
        &&      wiz_level(this_player(1)) < wiz_level(WIZLEVEL))
        {
                write("这个留言不是你写的。\n");
                return;
        }
        if(num == 0)
                notes = notes[num+1..sizeof(notes)-1];
        else
                notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
        set("notes", notes, ob);
        ob->save();
        write("删除第 " + (num+1) + " 号留言....Ok。\n");
        return;
}
varargs void view2(int line,string *text,object ob,int i)
{
        int w=line;
        if(i) w=w+17;
        write( YEL"－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n"NOR);
             printf("   总行数:"HIR+"%5d "NOR+"已阅读行数:"HIC+"%5d "+NOR CYN"(T"NOR"x"CYN")"NOR"翻到x行 "CYN"(U)"NOR"向上 "
             CYN"(D)"NOR"向下 "CYN"(R)"NOR"退出 "CYN"(B)"NOR"返回  \n",sizeof(text),w);
             write( YEL"－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n"NOR);
             write(YEL"您的选择："NOR);
             input_to((:do_more:),text,line,ob);
             return;
}
void do_more(string cmd,string *text,int line,object ob)
{
        int i,j,num;
        mapping *notes;
        string t=query_temp("select", this_player());
        string memer=query_temp("memer", this_player());
        if(!ob) ob=this_object();
        if(cmd[0]=='t')
        {
                j=atoi(cmd[1..<0]);
                if(j)
                {
                        line=j;
                        cmd="u";
                }
        }
        else if(j=atoi(cmd))
        {
                line=j;
                cmd="u";
        }
        if(cmd!="u"&&cmd!="d"&&cmd!="b"&&cmd!="r"){
                cmd="d";
                }
        switch(cmd) {
        case "d":
             case "D":
        //xkiller增加:本来屏幕就小还被占用那么多,---呵呵(增加的几个ascii图形更是无法显示)
                     write(ESC+"[1A"+ESC+"[200D"+ESC+"[K");
                write(ESC+"[1A"+ESC+"[200D"+ESC+"[K");
                write(ESC+"[1A"+ESC+"[200D"+ESC+"[K");
                write(ESC+"[1A"+ESC+"[200D"+ESC+"[K");
                if(line+17>=sizeof(text)) line=sizeof(text)-17;
                if(line<0) line=0;
                if(line<sizeof(text))
                {
 //                       write(YEL"--－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－--\n"NOR);
                               for(i=line + 17; line<sizeof(text) && line<i; line++)
                           write("  "+text[line] + "\n");
                               if( line>=sizeof(text) )
                           write(HIW"□□□－－－－－－－－－－－□ 全  文  完 □－－－－－－－－－－－－－－□□□\n"NOR);
                }
                view2(line,text,ob);
                return;
                break;
        case "u":
             case "U":
                if(line>=sizeof(text)) line=sizeof(text);
                       line = line - 23;
                       if(line<0) line=0;
                       write(YEL"--－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－--\n"NOR);
                       for(i=line + 23;line<sizeof(text)&&line < i;line++)
                       write("  "+text[line]+"\n");
                       if( line>=sizeof(text) )
                write(HIW"□□□－－－－－－－－－－－－□ 全  文  完 □－－－－－－－－－－－－－－□□□\n"NOR);
                       view2(line-23,text,ob,1);
                       return;
                       break;
        case "b":
             case "B":
                       return display(ob);
                       break;
        case "r":
             case "R":
                if(t=="post")
                {
                        num=query(memer, this_player());
                        notes=query("notes", ob);
                        do_post("[退出]"+notes[num]["title"],ob);
                }
                return;
        }
        view2(line,text,ob);
        return;
}
int register()
{
           object me;
           me = this_player();
           if( !query("register", me)){
                write(CLR"\n");
                 write(WHT"【使用者设定】        "YEL"【"+MUD_NAME+"注册单】\n"NOR);
                 write("\n");
                 write(YEL"目前选择：\n\n"NOR);
                 write(WHT"    您的代号     : "NOR);
                 input_to((:a:),this_player());
                 return 1;
        }
            write("你已经填写过注册单啦。\n");
             input_to("confirm_u_choice",this_player());
             return 1;
}
protected void a(string arg, string register)
{
           register = "代号     : "+arg+"\n";
           set_temp("register", register, this_player());
           write(WHT"    您的昵称     : "NOR);
           input_to((:b:),this_player(),register);
}
protected void b(string arg, string register)
{
           register = "昵称     : "+arg+"\n";
           set_temp("register", register, this_player());
           write(WHT"    真实姓名     : "NOR);
           input_to((:c:),this_player());
}
protected void c(string arg, string register)
{
           register = "姓名     : "+arg+"\n";
           set_temp("register", register, this_player());
           write(WHT"    联系地址     : "NOR);
           input_to((:d:),this_player());
}
protected void d(string arg, string register)
{
           register = "联系地址     : "+arg+"\n";
           set_temp("register", register, this_player());
           write(WHT"    工作单位/学校: "NOR);
           input_to((:e:),this_player());
}
protected void e(string arg, string register)
{
           register = "工作单位/学校: "+arg+"\n";
           set_temp("register", register, this_player());
           write(WHT"    电子信箱: "NOR);
           input_to((:f:),this_player());
}
protected void f(string arg, string register)
{
           register = "电子信箱: "+arg+"\n";
           set_temp("register", register, this_player());
           write(WHT"    联系电话: "NOR);
           input_to((:g:),this_player());
}
protected void g(string arg, string register)
{
           register = "联系电话: "+arg+"\n";
           set_temp("register", register, this_player());
           write(WHT"\n\n\n\n\n\n以上资料是否正确(Y/N)？(Q)取消注册 [N]:"NOR);
           input_to((:y:),this_player());
}
protected void y(string arg, string register)
{
           string table;
           if(arg=="") {
                   delete_temp("register", this_player());
                   register();
                   return ;
           }
        switch(arg[0]){
           case 'n':
             case 'N':
                   delete_temp("register", this_player());
                   register();
                   return ;
                   break;
           case 'y':
             case 'Y':
                   set("register", 1, this_player());
                   table=query_temp("register", this_player());
                   delete_temp("register", this_player());
                   write_file(REGISTER+query("id", this_player()),table,1);
                   write("◇设置一切正确。\n");
                   input_to("confirm_u_choice",this_player());
                   return;
                   break;
           case 'q':
             case 'Q':
                   delete_temp("register", this_player());
                   u_display();
                   write(YEL"\r请输入您的选择:"NOR);
                   input_to((:confirm_u_choice:),this_player());
                   return ;
                   break;
           default:
                   delete_temp("register", this_player());
                   register();
                   return ;
                   break;
             }
          return ;
}
int pager()
{
            object me;
            me = this_player();
            if( query_temp("call_on", me)){
                    write("打开 Pager 频道\n");
                    delete_temp("call_on", me);
            } else {
                   write("关闭 Pager 频道\n");
                   set_temp("call_on", 1, me);
           }
           return 1;
}
int cloak()
{
           object me;
           me = this_player();
           if(!wizardp(me))
            {
                   u_display();
                   write(YEL"\r请输入您的选择:"NOR);
                   input_to((:confirm_u_choice:),this_player());
                   return 1;
           }
           if( query("env/invisibility", me) )
           {
                    write("我要重现江湖...\n");
                    delete("env/invisibility", me);
            } else {
                    write("哈哈！我隐形起来了。\n");
                    set("env/invisibility", 5, me);
           }
          return 1;
}
int lock()
{
            object me,ob;
            me = this_player();
            ob=query_temp("link_ob", me);
            write(WHT"▲ 请输入注册密码，以解除萤幕锁定："NOR);
            input_to("get_old_pass", 1, ob);
            return 1;
}
protected void confirm_u_choice(string arg)
{
         set_temp("help_u", 1, this_player());
         if(arg=="") {
                     u_display();
                     write(YEL "\r请重新输入您的选择:"NOR);
                     input_to((:confirm_u_choice:),this_player());
                     return ;
             }
         switch(arg[0]){
            case 'r':
             case 'R':
                    register();
                    return ;
                    break;
            case 'p':
             case 'P':
                    pager();
                    write(YEL "\r请重新输入您的选择:"NOR);
                    input_to((:confirm_u_choice:),this_player());
                     return ;
                     break;
            case 'c':
             case 'C':
                    cloak();
                    write(YEL "\r请重新输入您的选择:"NOR);
                    input_to((:confirm_u_choice:),this_player());
                    return ;
                    break;
            case 'l':
             case 'L':
                    lock();
                    return ;
                    break;
            case 'f':
             case 'F':
            case 'h':
             case 'H':
            case 'g':
             case 'G':
                     m_display();
                     write(YEL "\r请输入您的选择:"NOR);
                     delete_temp("help_u", this_player());
                     input_to((:confirm_main_choice:),this_player());
                     return ;
                     break;
            default:
                   u_display();
                   write(YEL"\r请输入您的选择:"NOR);
                   input_to((:confirm_u_choice:),this_player());
                   return ;
        }
          return;
}
void u_display()
{
              view_main();
              if (wizardp(this_player()))
              write("                       "CYN"(Ｃ)"NOR"loak       隐身术\n");
              write("                       "CYN"(Ｌ)"NOR"ockScreen  锁定萤幕\n");
              write("                       "CYN"(Ｒ)"NOR"egister    江湖注册\n");
              write("                       "CYN"(Ｐ)"NOR"ager       呼叫器开关\n");
              write("                       "CYN"(Ｇ)"NOR"return     返回主菜单\n");
              view_main_1();
}
void get_old_pass(string pass, object ob)
{
        string old_pass;
        old_pass=query("password", ob);
        if( crypt(pass, old_pass)!=old_pass ) {
                lock();
                return ;
        }
        u_display();
        write(YEL"\r请输入您的选择:"NOR);
        input_to((:confirm_u_choice:),this_player());
        return ;
}
string find_file()
{
         string str=query_temp("select", this_player());
        str=DIR+str+".h";
         return str;
}
void getname1(string arg)
{
        int k;
        if(!arg||arg=="")
        {
                write(CYN"请输入链接名称："NOR);
                input_to("getname1");
                return;
        }
        if(arg=="q"||arg=="Q")
        {
                display();
                return;
        }
        k=strlen(arg);
        if(k<2||k>16)
        {
                write(GRN"链接名称字数必须在2到16个字元之间！\n"NOR);
                write(CYN"请输入链接名称："NOR);
                input_to("getname1");
                return;
        }
        write(GRN"请输入链接档案( Q 放弃）："NOR);
        input_to("getname2",arg);
        return;
}
void getname2(string str,string arg)
{
        string file=read_file(find_file()),msg,t;
        string *text, *w;
        if(str=="q"||str=="Q")
        {
                display();
                return;
        }
        if(file_size(str)<0)
        {
                write(YEL"没有这个档案！\n"NOR);
                write(GRN"请输入链接档案："NOR);
                input_to("getname2",arg);
                return;
        }
        if(!file) file="";
        file+=arg+"==@=="+str+"\n";
        text=explode(file,"\n");
        file="";
        while(sizeof(text))
        {
                msg=text[0];
                text-=({msg});
                w=explode(msg,"==@==");
                t=replace_string(find_file(),".h","");
                t=t+"/"+w[1]+".h";
                if(file_size(w[1])<0&&file_size(t)<0)
                continue;
                file+=msg+"\n";
        }
        write_file(find_file(),file,1);
        write("OK!\n");
        display();
        return;
}
void view7(string arg)
{
        int k;
        string file=read_file(find_file()),*text;
        if(!arg)
        {
                write(CYN"请选择要修改的选项：(Q键取消)"NOR);
                input_to("view7");
                return;
        }
        if(arg=="q"||arg=="Q")
        {
                display();
                return;
        }
        if(!k=atoi(arg))
        {
                view7(0);
                return;
        }
        text=explode(file,"\n");
        if(k>sizeof(text))
        {
                view7(0);
                return;
        }
        k--;
        write(YEL"您要修改(1)名称或者(2)链接？"NOR);
        input_to("view8",text[k],k);
        return;
}
void view8(string arg,string str,int k)
{
        string *w = explode(str,"==@==");
        switch(arg) {
                case "1":
                write(CYN"请输入名称:"NOR);
                input_to("view9",str,k,1);
                return;
                case "2":
                if(file_size(w[1])<0&&strsrch(w[1],"subdir")>-1)
                {
                        write(GRN"这是一个目录,不是链接文档!\n"NOR);                                 view7(0);
                        return;
                }
                write(CYN"请输入链接文档:"NOR);
                input_to("view9",str,k,0);
                return;
        }
        view7(0);
        return;
}
void view9(string arg,string str,int i,int j)
{
        string file=read_file(find_file()),
        *text=explode(file,"\n"),
        *w=explode(str,"==@==");
        if(j) w[0]=arg;
        else {
                if(file_size(arg)<0)
                {
                        write(RED"没有这个文档!\n"NOR);
                        view8("2",str,i);
                        return;
                }
                w[1]=arg;
        }
        text[i]=implode(w,"==@==");
        file=implode(text,"\n");
        write_file(find_file(),file,1);
        write("OK!\n");
        display();
        return;
}
void view3()
{
        string file,*text,str=find_file(),*w,msg,*t;
        int i,j;
        file=read_file(str);
        if(!file)
        {
                write("资料采集中......\n");
                return;
        }
        text=explode(file,"\n");
        if(!j=sizeof(text))
        {
                write("资料采集中......\n");
                return;
        }
        t=({});
        file="";
        i=0;
        while(sizeof(text))
        {
                w=explode(text[0],"==@==");
                file+=sprintf(HIC" ("BBLU +HIY"%2d"NOR +HIC")"WHT"【%|16s】"NOR,i+1,text[0]);
                // file+=sprintf(HIC" ("BBLU +HIY"%2d"NOR +HIC")"WHT"【%|16s】"NOR,i+1,w[0]);
                if(i%3==2) file+="\n";
                text-=({text[0]});
                i++;
        }
        file+="\n";
        // write(file);
        this_player()->start_more(file);
        return;
}
void view4()
{
        string file,*w,*text,str=find_file();
        int i,j,k,v;
        file=read_file(str);
        if(!file)
        {
                write("资料采集中......\n");
                return;
        }
        text=explode(file,"\n");
        if(!j=sizeof(text))
        {
                write("资料采集中......\n");
                return;
        }
        for(file="",i=0;i<j;i++)
        {
                w=explode(text[i],"==@==");
                file+=sprintf(CYN" (%2d)"WHT"【%|16s】%s"NOR,i+1,w[0],w[1]);
                if(i%2==1) file+="\n";
        }
        file+="\n";
        write(file);
        return;
}
void view5(string arg)
{
        int k=atoi(arg),i,j;
        string *w, *text;
       string file,t=query_temp("select", this_player());
        file=find_file();
        file=read_file(file);
        if(!file) {
                write(RED"没有链接文件!\n"NOR);
                display();
                return;
        }
        if(arg=="q"||arg=="Q")
        {
                write(CYN"返回！\n"NOR);
                display();
                return;
        }
        if(!k)
        {
                write(GRN"请输入你要查看的内容:"NOR);
                input_to("view5");
                return;
        }
        text=explode(file,"\n");
        if(j=sizeof(text)<k-1)
        {
                write(GRN"没有这个文件!\n"NOR);
                write(GRN"请输入你要查看的内容:"NOR);
                input_to("view5");
                return;
        }
        k--;
        w=explode(text[k],"==@==");
        file=read_file(w[1]);
        if(file) {
                start_help(color_filter(file),this_object());
                return;
        }
        t=t+"/"+w[1];
        if(file_size(DIR+t+".h")<0)
        {
                write(GRN"没有这个文件!\n"NOR);
                write(GRN"请输入你要查看的内容:"NOR);
                input_to("view5");
                return;
        }
        set_temp("select", t, this_player());
        display();
        return;
}
void delfile(string arg)
{
        int k=atoi(arg),v;
        string *text, *w;
        string str=find_file(),file=read_file(str),t;
        if(arg=="q"||arg=="Q")
        {
                display();
                return;
        }
        if(k<1)
        {
                write(CYN"你要删除第几号链接:"NOR);
                input_to("delfile");
                return;
        }
        text=explode(file,"\n");
        if(v=sizeof(text)<k)
        {
                write(GRN"没有这个链接!\n");
                write(CYN"你要删除第几号链接:"NOR);
                input_to("delfile");
                return;
        }
        --k;
        w=explode(text[k],"==@==");
        text-=({text[k]});
        file=implode(text,"\n");
        write_file(str,file,1);
        t=replace_string(find_file(),".h","");
        t=t+"/"+w[1]+".h";
        if(rm(t))
        {
        }
        write("OK!\n");
        display();
        return;
}
varargs void display(object ob)
{
        int i;
        object me=this_player();
       string v,t=query_temp("select", me);
        if(!ob) ob=this_object();
        if( v=query_temp("memer", me) )
        {
                i=query(v, me);
                view_main_k();
                view1();
                write(view_msg(i,ob));
                view_main_1();
                write(YEL "\r请输入您的选择:"NOR);
                     input_to((:confirm_p_choice:),ob);
                     return;
        }
        if(t=="board")
        {
                view6();
                return;
        }

        view_main();
        view3();
        view_main_1();
        write(BRED +CYN"(B)"NOR +BRED"返回 "NOR);
        if(wiz_level(WIZLEVEL)<=wiz_level(me))
        write(BRED +CYN"  (A)"NOR+BRED"加入 "CYN+BRED"(C)"NOR+BRED"修改 "CYN+BRED"(D)"NOR
        +BRED"删除 "CYN+BRED"(S)"NOR+BRED"查看 "CYN+BRED"(M)"NOR+BRED"新建"NOR);
        write("\n");
        write(YEL "\r请输入您的选择:"NOR);
        input_to((:confirm_choice:),this_player());
}
protected void confirm_choice(string arg)
{
        object me=this_player();
       string t=query_temp("select", me);
        string *text;
        int k=atoi(arg);
        int p;
        if(k>0)
        {
                view5(arg);
                return;
        }
             switch(arg)
             {
                     case "b":
                     case "B":
                     text=explode(t,"/");
                     if(sizeof(text)<2)
                     {
                             main(me,0);
                             return;
                     }
                     text-=({text[sizeof(text)-1]});
                     t=implode(text,"/");
                     set_temp("select", t, me);
                     display();
                     return;
                     break;
                     case "c":
                     case "C":
                     view7(0);
                     return;
                     break;
                case "a":
                     case "A":
                if(wiz_level(me)<wiz_level(WIZLEVEL))
                {
                        write(RED"你的权限不足，不能修改这里的档案！\n");
                        return;
                }
                write(CYN"请输入链接名称："NOR);
                input_to("getname1");
                return;
                break;
                case "d":
                     case "D":
                if(wiz_level(me)<wiz_level(WIZLEVEL))
                {
                        write(RED"你的权限不足，不能修改这里的档案！\n");
                        return;
                }
                write(CYN"你要删除第几号链接:"NOR"(“Q”取消)");
                input_to("delfile");
                return;
                break;
                case "s":
                     case "S":
                view_main();
                view4();
                view_main_1();
                write(BRED +CYN"(B)"NOR +BRED"返回 "NOR);
                if(wiz_level(WIZLEVEL)<=wiz_level(me))
                write(BRED +CYN"  (A)"NOR+BRED"加入 "CYN+BRED"(C)"NOR+BRED"修改 "CYN+BRED"(D)"NOR
                +BRED"删除 "CYN+BRED"(S)"NOR+BRED"查看 "CYN+BRED"(M)"NOR+BRED"新建"NOR);
                write("\n");
                write(YEL "\r请输入您的选择:"NOR);
                input_to((:confirm_choice:),me);
                return;
                break;
                case "m":
                     case "M":
                if(wiz_level(me)<wiz_level(WIZLEVEL))
                {
                        write(RED"你的权限不足，不能修改这里的档案！\n");
                        return;
                }
                write(CYN"请输入目录名称："NOR);
                input_to("getname3");
                return;
        }
        display();
        return;
}
void view6()
{
        int i,j,k,wizlvl;
        string *file;
        string name,str="",msg;
        object ob;
        view_main();
        delete_temp("memer", this_player());
        if(file_size(BOARDCENTER)>-1)
        {
                str=read_file(BOARDCENTER);
                write(str);
        }
        else {
                file=get_dir(BOARD+"*.c");
                for(i=0;i<sizeof(file);i++)
                {
                        if(!ob=find_object(BOARD+file[i]))
                        ob=load_object(BOARD+file[i]);
                        if( !ob || !query("board_id", ob) )
                                continue;
                        if( (wizlvl=query("wizlvl", ob)) && wizlvl>wiz_level(this_player()) )
                                continue;
                        name=query("name", ob);
                        name=replace_string(name,"板","");
                        name=replace_string(name,"簿","");
                        name=replace_string(name,"册","");
                        name=replace_string(name,"弟子","");
                        name=replace_string(name,"报告","");
                        name=replace_string(name,"留言","");
                        name=replace_string(name,"记事","");
                        name=replace_string(name,"教众","");
                        name=replace_string(name,"版","");
                        if(strlen(name)>16)
                        name=name[0..15];
//                        destruct(ob);
                        msg=sprintf(" 『"HIC +BBLU+"%2d"NOR+"』"+(wizlvl?YEL:WHT)+"【%|16s】"NOR,i+1,name);
                        str+=msg;
                        write(msg);
                        ++j;
                        if(j==3)
                        {
                                j=0;
                                write("\n");
                                str+="\n";
                        }
                }  if(j==3) {
                        write("\n");
                        str+="\n";
                }
                str+=sprintf(" 『"HIC +BBLU+"%2s"NOR+"』"+WHT+"【%|16s】\n"NOR,"B","返回主菜单");
                printf(" 『"HIC +BBLU+"%2s"NOR+"』"+WHT+"【%|16s】\n"NOR,"B","返回主菜单");
                write_file(BOARDCENTER,str,1);
        }
        view_main_1();
        input_to((:confirm_k_choice:),this_player());
        return;
}
protected void confirm_k_choice(string arg)
{
        int k=atoi(arg);
        string *file=get_dir(BOARD+"*.c");
        string dir;
        object ob;
        if(arg=="b")
        {
                main(this_player(),0);
                     return;
             }
             else if(!k)
             {
                     write(CYN"请输入您的选择:"NOR);
                     input_to((:confirm_k_choice:),this_player());
                return;
        }
        --k;
        dir=BOARD+file[k];
        if(!ob=find_object(dir))
        ob=load_object(dir);
        if( !ob || !query("board_id", ob) || query("wizlvl", ob)>wiz_level(this_player()) )
        {
                write(CYN"没有这个留言板!\n请输入您的选择:"NOR);
                     input_to((:confirm_k_choice:),this_player());
                return;
        }
        ob->restore();
        set_temp("memer", "post/"+file[k], this_player());
        display(ob);
        return;
}
void getname3(string arg)
{
        int k;
       string dir,t=query_temp("select", this_player()),
        *text,msg,*w,file=read_file(find_file());
        if(!file) file="";
        if(!arg||arg=="")
        {
                write(CYN"请输入目录名称："NOR);
                input_to("getname3");
                return;
        }
        if(arg=="q"||arg=="Q")
        {
                display();
                return;
        }
        k=strlen(arg);
        if(k<2||k>16)
        {
                write(GRN"目录名称字数必须在2到16个字元之间！\n"NOR);
                write(CYN"请输入目录名称："NOR);
                input_to("getname3");
                return;
        }
        dir=replace_string(find_file(),".h","");
        mkdir(dir);
        for(k=0;;k++)
        {
                t="subdir"+k;
                msg=dir+"/"+t+".h";
                if(file&&strsrch(file,t)<0)
                rm(msg);
                if(file_size(msg)>-1)
                continue;
                break;
        }
        file+=arg+"==@=="+t+"\n";
        text=explode(file,"\n");
        file="";
        write_file(msg,"",1);
        while(sizeof(text))
        {
                msg=text[0];
                text-=({msg});
                w=explode(msg,"==@==");
                t=replace_string(find_file(),".h","");
                t=t+"/"+w[1]+".h";
                if(file_size(w[1])<0&&file_size(t)<0)
                continue;
                file+=msg+"\n";
        }
        write_file(find_file(),file,1);
        write("OK!\n");
        display();
        return;
}


int help(object me)
{
  write(@HELP

泥潭游戏中的在线ＢＢＳ系统，从游戏的帮助到玩家的交流
内容丰富，操作简便。
HELP
    );
    return 1;
}
