// 彩票投注系统 made by 叶雨飞(sunyc)@kync 2001/1/26
// remodify by Sunyc@kync 2002/7/24
// remodify By Sunyc@kync.tomud.com 5555 2002/11/24
// 更换奖金，可以累计，也不只是gold了
// 改为30选7

#include <ansi.h>
#include <localtime.h>
inherit ITEM;
inherit F_SAVE;
inherit F_NOCLONE;

mixed *all_biao;
nosave string *touzhu;

int do_read(string);
int do_ya(string);
void enough_rest();
string show_player();
void auto_post(string title, string body);

string query_save_file()
{
        return DATA_DIR + "caipiao";
}

void create()
{
        set_name(HIG "彩票投注板" NOR, ({ "touzhu ban", "touzhu", "ban"}) );
        set("long",
                "这是全体玩家的彩票投注板。\n"
                "如何购买彩票请read rules，\n");
        set_weight(900000000);
        seteuid(getuid());
        set("unit", "块");
        set("no_put", 1);
        set("no_get", 1);

        set("times", 1);
        restore();
        set("startroom", "/d/city/qiyuan/xxzl1");
        check_clone();
}

void init()
{
        add_action("do_read", "read");
        add_action("do_ya", "touzhu");
        add_action("do_duijiang", "duijiang");
}

void enough_rest()
{
        delete_temp("busy");
}

int do_ya(int arg)
{
        object me, ob, caipiao;
        mapping biao;
        string str;
        int i;

        me = this_player();
        str = "";

        //if( query("balance", me)/10000<10 )
                //return notify_fail("钱庄至少要有十两黄金才能投注。\n");
        if( MEMBER_D->db_query_member(me, "money") < 2 )
                return notify_fail("你至少要有2NT才能投注。\n");

        if( query("end_ya") || query("duijiang") )
                return notify_fail("截止时间已过，等下次再来买吧......\n");

        if( query_temp("busy") )
                return notify_fail("请稍候几秒钟再试...\n");

        //if( !intp(arg) || !arg ) {
        if( !query_temp("z_num", me) ) {
                tell_object(me,"请选7个30以内的号码，用逗号隔开。\n");
                tell_object(me,"例如：2,3,4,5,6,7,8\n");
                tell_object(me,"或者输入-1进行机选。\n");
                tell_object(me,"请输入您的选择：");
                input_to("touzhu_1",me);
                return 1;
        } else {
                message_vision("$N把投票单写好后，扔进了投票板。天上突然掉下了一张彩票，$N连忙揣了起来。\n",me);
                //addn("balance", -100000, me);
                //tell_object(me,"钱庄已经扣除了你十两黄金。请在"+query("kaijiang_cdate")+"来等待结果吧！\n");
                if( !MEMBER_D->player_pay(me, 2) )
                {
                        tell_object(me,"交易失败。\n");
                        return 1;
                }
                tell_object(me,"已经扣除了你2NT。请在"+query("kaijiang_cdate")+"来等待结果吧！\n");
                tell_object(me,HIR"ＧＯＯＤ　ＬＵＣＫ 祝您好运！\n"NOR);
                caipiao=new("/clone/misc/caipiao.c");
                set("kaijiang_date", query("kaijiang_cdate"), caipiao);
                // 获得一个连续字符串
                for(i=0;i<sizeof(query_temp("z_num", me));i++)
                        str+=query_temp("z_num", me)[i]+"";
                set("z_num", str, caipiao);
                set("times", query("times"), caipiao);
                caipiao->move(me);
                set("crypt", oldcrypt(str,0), caipiao);
                biao = ([
                        "id":query("id", me),
                        "name"  :me->name(1),
                        "z_num" :str,
                        "z_num_all":query_temp("z_num",me),
                        "jieguo":"未开奖",
                ]);
                delete_temp("z_num", me);
                if( !pointerp(all_biao) ) all_biao = ({biao});
                else all_biao += ({biao});
                save();
                remove_call_out("enough_rest");
                call_out("enough_rest", 1);
                return 1;
        }
        return 1;
}

void touzhu_1(string num,object me)
{
        int i,z,j=0;
        int h,k,p=0;
        int *jieguo=({});
        string str;
        int *tmp = ({});

        if( !num || num=="" )
        {
                tell_object(me,"请选7个1-30中的号码，用逗号隔开。\n");
                tell_object(me,"例如：2,3,4,5,6,7,8\n");
                tell_object(me,"或者输入-1进行机选。\n");
                tell_object(me,"请输入您的选择：");
                input_to("touzhu_1", me);
                return;
        }
        if( atoi(num)==-1 )
        {
                i=0;
                z=0;
                str="";
                while( p!=7 )
                {
                        i=random(30)+1;
                        if(member_array(i,jieguo)!=-1) continue;
                        else
                        {
                                jieguo+=({i});
                                p++;
                                continue;
                        }
                }
                for( i=0;i<sizeof(jieguo);i++ )
                        str+=jieguo[i]+" ";
                set_temp("z_num", jieguo, me);
                write("\n您的投注号码为"HIR+str+NOR"，您确定么?[y/n]：");
                input_to("yn",me);
                return;
        }
        touzhu=explode(num,",");
        str="";
        for(i=0;i<sizeof(touzhu);i++)
        {
                if( !intp(z=atoi(touzhu[i])) || z<1 || z>30 || sizeof(touzhu)!=7)
                {
                        j=1;
                        break;
                }
                if( member_array(z,tmp)==-1 )
                        tmp+=({z});
                str+=" "+z;
        }
        if( sizeof(tmp)!=7 ) j=1;
        if( j )
        {
                tell_object(me,"请选7个1-30中的号码，用逗号隔开。\n");
                tell_object(me,"例如：2,3,4,5,6,7,8\n");
                tell_object(me,"或者输入-1进行机选。\n");
                tell_object(me,"请输入您的选择：");
                input_to("touzhu_1", me);
                return;
        }
        set_temp("z_num", tmp, me);
        write("\n您的投注号码为"HIR+str+NOR"，您确定么?[y/n]：");
        input_to("yn",me);
        return;
}
void yn(string yn,object me)
{
        if( (yn[0]!='y' && yn[0]!='Y') ) {
                delete_temp("z_num", me);
                write("\n好吧，请重新投注。");
                tell_object(me,"请选7个1-30中的号码，用逗号隔开。\n");
                tell_object(me,"例如：2,3,4,5,6,7,8\n");
                tell_object(me,"请输入您的选择：");
                input_to("touzhu_1", me);
                return;
        }
        else {
                write("\n储存数据中...\n");
                do_ya(1);
                return;
        }
}

//void check(string yn,object me)
void check(object me)
{
        int money=0;
        int i;
        /*query_temp("check", if( oldcrypt(me),yn) != yn){
                write("对不起，您输入的校验码有误，不能给您发奖。\n");
                delete_temp("check", me);
                return;
        }
        else {   */
        write("\n恭喜您中了本期大奖...\n");
        delete_temp("check", me);
        write("ok...开始发奖\n");
        switch (all_biao[query_temp("num",me)]["jieguo"])
        {
        case "特等奖":money=query("last_gold");
                break;
        case "一等奖":money=query("last_gold")/5;
                break;
        case "二等奖":money=query("last_gold")/10;
                break;
        case "三等奖":money=query("last_gold")/500;
                break;
        case "四等奖":money=query("last_gold")/10000;
                break;
        }

        MEMBER_D->db_pay_member(me, money);

        write(HIR"你中了"+chinese_number(money)+" NT,已经拨入你的账户！\n");
        message("system",HIW"〖福彩〗："+HIC" "+query("name",me)+HIW" 中了"+HIY" "+chinese_number(money)+HIW" NT，已经拨入帐户！\n"NOR,users());
        all_biao[query_temp("num",me)]["jieguo"]="已兑奖";
        //all_biao-=({query_temp("num", all_biao[me)]});
        save();//存盘
        delete_temp("num", me);
        delete_temp("check", me);
        remove_call_out("enough_rest");
        call_out("enough_rest", 1);
        return;
 //   }
}

int do_read(string arg)
{
        int i,j,k;
        object me;
        string name,str,str1,str2;
        mapping biao;

        me = this_player();

        if( arg == "rules" )
        {
                write("本彩票系统已经开通，欢迎大家前来购彩。\n");
                write("投注请用touzhu\n");
                write("查询请用read biao\n");
                write("查询规则请用read duijiang\n");
                write("请使用duijiang指令，你的奖金将自动进入你帐户。\n");
                return 1;
        }
        if( arg == "biao" )
        {
                /*if( !pointerp(all_biao) || !sizeof(all_biao) )
                {
                        write("\n还没有人开始投注。\n");
                        return 1;
                }*/
                write(show_player());
                return 1;
        }
        if( arg == "duijiang" )
        {
                write("兑奖细则：\n");
                write("特等奖：七个数字全部吻合。      ——全部累计奖金.\n");
                write("一等奖：共有六个数字吻合。      ——全部累计奖金/5.\n");
                write("二等奖：共有五个数字吻合        ——全部累计奖金/50.\n");
                write("三等奖：共有四个数字吻合        ——全部累计奖金/500.\n");
                write("四等奖：仅有三个数字吻合        ——全部累计奖金/10000.\n");
                write("祝您玩得痛快!\n");
                return 1;
        }
        else
                write("你要看什么？购买规则请read rules，购买情况请read biao,兑奖规则请read duijiang。\n");
        return 1;
}

string show_player()
{
        int z,j,k,i,h, m;
        string str="";
        int *str_te,*str_1,*str_2,*str_3,*str_4,*str_5,*list, *str_old;
        mapping name;

        i=0;
        if( !query("duijiang") )
        {
                h=sizeof(all_biao);
                str+=HIW"本期彩票已有 "HIG+chinese_number(sizeof(all_biao))+HIW" 位玩家投注，投注状况如下：\n"NOR;
                str+="┏------------┳----------------------┳------┓\n";
                while (i<h)
                {
                        name=all_biao[i];
                        str+= sprintf("┃%-12s┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,name["z_num"],name["jieguo"],);
                        i++;
                }
                str+="┗------------┻----------------------┻------┛\n"NOR;
                if( query("end_cdate") ) str+=HIW"本期投注截止时间："HIY+query("end_cdate")+HIW"\n本期彩票开奖时间："HIM+query("kaijiang_cdate")+"\n"NOR;
                else str+=HIR"本期彩票已经截止购买,"HIW"开奖时间："HIG+query("kaijiang_cdate")+HIW"。\n"NOR;
                str+=HIW"本期彩票累计奖金："HIY+query("all_gold")+HIG" NT。\n"NOR;
                return str;
        }
        str_te=str_1=str_2=str_3=str_4=str_5=list=str_old=({});
        str=HIW"第 "HIY+chinese_number(query("times")-1)+ HIW" 期彩票大奖已开出："+HIR+query("last_z_num_str")+NOR+"\n";
        str+=HIW"已有 "HIG+chinese_number(sizeof(all_biao))+HIW" 个玩家投注，中奖玩家如下：\n"NOR;
        i=0;
        h=sizeof(all_biao);
        for(i=0;i<h;i++)
        {
                k=0;
                for(z=0;z<sizeof(query("last_z_num"));z++)
                {
                        j=all_biao[i]["z_num_all"][z];
                        if(member_array(j,query("last_z_num"))!=-1) k++;
                }

                if ( all_biao[i]["jieguo"] == "已兑奖")
                        str_old+=({i});
                else
                {
                        switch (k){
                        case 7:
                                str_te+=({i});
                                all_biao[i]["jieguo"]="特等奖";
                                break;
                        case 6:
                                str_1+=({i});
                                all_biao[i]["jieguo"]="一等奖";
                                break;
                        case 5:
                                str_2+=({i});
                                all_biao[i]["jieguo"]="二等奖";
                                break;
                        case 4:
                                str_3+=({i});
                                all_biao[i]["jieguo"]="三等奖";
                                break;
                        case 3:
                                str_4+=({i});
                                all_biao[i]["jieguo"]="四等奖";
                                break;
                        default:
                                str_5+=({i});
                                all_biao[i]["jieguo"]="无奖";
                                break;
                        }
                }
        }
        save();
        list+=str_te+str_1+str_2+str_3+str_4+str_old;
        str_te=str_1=str_2=str_3=str_4=str_5=str_old=({});
        str+="┏------------┳----------------------┳------┓\n";
        str+= sprintf("┃%-12s┃%-22s┃%-6s┃\n","玩家名","  投   注   号   码   ","所中奖");
        str+="┣------------╋----------------------╋------┫\n";
        z=0;
        h=sizeof(list);
        set("zhongjiang_num",h);
        m = 0;
        while (z<h)
        {
                i=list[z];
                name=all_biao[i];
                str+= sprintf("┃%-12s┃%22s┃%-6s┃\n",HIR+name["name"]+NOR,(int)name["z_num"],name["jieguo"],);
                if ( name["jieguo"] != "已兑奖" )
                        m++;
                z++;
        }
        list=({});
        str+="┗------------┻----------------------┻------┛\n"NOR;
        str+=HIW"本期尚未兑奖注数："HIM+chinese_number(m)+HIW"\n"NOR;
        str+=HIW"下期彩票发行时间："HIG+query("start_cdate")+HIW"\n"NOR;
        str+=HIW"下期彩票预计奖金："HIY+query("all_gold")+HIW" NT。\n"NOR;
        //return "/feature/more.c"->start_more(str);
        return str;
}

int do_duijiang()//兑奖指令
{
        int i,j,k,m,n,money;
        object me;

        me = this_player();
        if( !query("duijiang") )
                return notify_fail("还未到兑奖时间！\n");
        if( query_temp("busy") )
                return notify_fail("稍候........\n");
        set_temp("busy",1);
        j=sizeof(all_biao);
        k=0;
        i=0;
        m = 0;
        n = 0;
        while ( i < j )
        {
                if( all_biao[i]["id"] == query("id", me) && all_biao[i]["name"] == query("name", me) )
                {
                        n = 1;
                        if ( all_biao[i]["jieguo"] != "已兑奖" && all_biao[i]["jieguo"] != "无奖" )
                        {
                                k = i + 1;
                                break;
                        }
                        else if ( all_biao[i]["jieguo"] == "已兑奖" )
                                m = 1;
                        else if ( all_biao[i]["jieguo"] == "无奖" )
                                m = 2;
                }
                i++;
        }
        delete_temp("busy");
        if( !n || n == 0 ) return notify_fail("你并没有买彩票呀！\n");
        else if ( k )
        {
                set_temp("check", all_biao[k-1]["z_num"]+""+all_biao[k-1]["t_num"], me);
                set_temp("num", k-1, me);
                write("您的中奖号码是"+query_temp("check", me)+"。\n");
                //write("请输入您的校验码:");
                //input_to("check",me);
                check(me);
                return 1;
        }
        else if( m == 1 ) return notify_fail("你已经兑过奖了！\n");
        else if( m == 2 ) return notify_fail("你根本没中奖，来兑个屁！\n");
}

void auto_post(string title,string body)
{
        mapping note;
        note = allocate_mapping(4);
        note["title"] = title;
        note["author"] ="彩票板";
        NEWS_D->done_post(this_object(),note,body);
        return;
}
void clean_data()
{
        all_biao=({});
        save();
}
