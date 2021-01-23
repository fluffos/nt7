// matong.c

#include <ansi.h>
inherit NPC;
#define MJ_DATA "/data/mj_data.o"
#define END 286
#define START 0
void check_flower(mapping who);
int to_say_play();
int to_say_rule();
int do_check_Mj(string datastr,string str);
int do_check_eat(string num1,string num2,string LastDump);
int delete_last_dump(string whoId);
int do_check_win(string str);
int check_hu(string strW);
int set_mjdata(object me,int *winner);
int *get_mjdata(string id);
int get_tc(mapping who);
varargs int do_da(string str,object me);
varargs int do_touch(string str,object me);
varargs int wash_mj(int amount);
varargs int do_win(string str,object me);
varargs int do_gang(string str,object me);
varargs int do_peng(string str,object me);
string check_id(string str,string kind);
string do_delete_Mj(string datastr,string str,int amount);
string show_mj(string str,int flag);
string sort_data(string str);
mixed do_check_num(string str,int flag);
//牌资料
string MjE= "1w2w3w4w5w6w7w8w9w1t2t3t4t5t6t7t8t9t1s2s3s4s5s6s7s8s9seasowenojofabaf1f2f3f4f5f6f7f8";
string *MjC = ({"",
        "一万","二万","三万","四万","五万","六万","七万","八万","九万",
        "一筒","二筒","三筒","四筒","五筒","六筒","七筒","八筒","九筒",
        "一索","二索","三索","四索","五索","六索","七索","八索","九索",
        "东风","南风","西风","北风","红中","青发","白板",
        "1 春","2 夏","3 秋","4 冬","1 梅","2 兰","3 竹","4 菊","暗杠 "
});
int K;
string Tc = "";
//资料
int Auto;
int Auto_Tin;
int Auto_Gang;
int Auto_Peng;
int Count;
int count;
int end;
int Goned;
int HU_F;
int NO_HU;
int NO_GANG;
int Playing;
int Play;
int Times;
int Touched;
int NowPlayer;
string List ="";
string LookP ="";
string *NowPlayerId = ({ "","","","" });
string LastDumpId="";
string LastDump="";

mapping P1Data = ([
"Show":"color","Id":"","Name":"","Mj":"","Out":"","OutGang":"","OutPeng":"",
"OutFlower":"","Auto":"","AutoTin":"","AutoGang":"","AutoPeng":"","Dump":""
]);
mapping P2Data = ([
"Show":"color","Id":"","Name":"","Mj":"","Out":"","OutGang":"","OutPeng":"",
"OutFlower":"","Auto":"","AutoTin":"","AutoGang":"","AutoPeng":"","Dump":""
]);
mapping P3Data = ([
"Show":"color","Id":"","Name":"","Mj":"","Out":"","OutGang":"","OutPeng":"",
"OutFlower":"","Auto":"","AutoTin":"","AutoGang":"","AutoPeng":"","Dump":""
]);
mapping P4Data = ([
"Show":"color","Id":"","Name":"","Mj":"","Out":"","OutGang":"","OutPeng":"",
"OutFlower":"","Auto":"","AutoTin":"","AutoGang":"","AutoPeng":"","Dump":""
]);
void create()
{
        set_name("麻童",({"ma tong","matong","kid"}));
        set_weight(1);
        set("long","一个脸上生了一些小麻子的小孩。");
        set("inquiry",([
                "mj": (: to_say_play :),
                "麻将": (: to_say_play :),
                "玩法": (: to_say_play :),
                "play": (: to_say_play :),
                "规则": (: to_say_rule :),
                "rule": (: to_say_rule :),
        ]));
        setup();
        seteuid(getuid());
}
void init()
{
        add_action("do_sit","sit");
        add_action("do_sit","join");
        add_action("do_da","da");
        add_action("do_da","play");
        add_action("do_da","dump");
        add_action("do_eat","eat");
        add_action("do_eat","chi");
        add_action("do_gang","gang");
        add_action("do_win","hu");
        add_action("do_win","win");
        add_action("do_help","help");
        add_action("do_look","look");
        add_action("do_look",".");
        add_action("do_look",".1");
        add_action("do_look",".2");
        add_action("do_look",".3");
        add_action("do_look",".4");
        add_action("do_look","..");
        add_action("do_touch","mo");
        add_action("do_touch","0");
        add_action("do_peng","peng");
        add_action("do_restart","chonglai");
        add_action("do_restart","restart");
        add_action("wash_mj","start");
        add_action("wash_mj","kaishi");
        add_action("wash_mj","xipai");
        add_action("do_setmj","setmj");
        add_action("show_top","top");
        add_action("ch","ch");
}
int do_sit()
{
        object me=this_player();
        if( query("id", me) == P1Data["Id"]
         || query("id", me) == P2Data["Id"]
         || query("id", me) == P3Data["Id"]
         || query("id", me) == P4Data["Id"] )
        {
                if(!Playing) message_vision("$N坐在地上蹬着腿儿耍泼，瘪着嘴儿哭哭啼啼。\n",me);
                else message_vision("$N搓了搓手，呵了一口气：今天自摸"+(random(12)+1)+"次就好。\n",me);
                return 1;
        }
        if (Playing)
        {
                if (random(1))
                        message_vision(this_object()->name()+
                        "指着"+me->name()+"说道：人家正玩着呢，您到旁边坐会儿吧。\n",me);
                else
                        message_vision("$N坐在地上蹬腿儿耍泼，瘪着嘴儿哭哭啼啼地嚷嚷：我也要玩啦～～。\n",me);
                return 1;
        }
        if (!P1Data["Id"] || P1Data["Id"]=="")
        {
                P1Data["Id"]=query("id", me);
                NowPlayerId[Play]=query("id", me);
                message_vision("$N加入了这场牌局。\n",me);
                Play++;
                Times=0;
                LookP+="在前面有"+me->name()+"，";
                return 1;
        } else if (!P2Data["Id"] || P2Data["Id"]=="")
                {
                        P2Data["Id"]=query("id", me);
                        message_vision("$N加入了这场牌局。\n",me);
                        NowPlayerId[Play]=query("id", me);
                        Play++;
                        Times=0;
                        LookP+=me->name()+"，";
                        return 1;
                } else if (!P3Data["Id"] || P3Data["Id"]=="")
                        {
                                P3Data["Id"]=query("id", me);
                                message_vision("$N加入了这场牌局。\n",me);
                                NowPlayerId[Play]=query("id", me);
                                Play++;
                                Times=0;
                                LookP+=me->name()+"，";
                                return 1;
                        } else if (!P4Data["Id"] || P4Data["Id"]=="")
                                {
                                        P4Data["Id"]=query("id", me);
                                        message_vision("$N加入了这场牌局。\n",me);
                                        NowPlayerId[Play]=query("id", me);
                                        Play++;
                                        Times=0;
                                        LookP+=me->name();
                                        return wash_mj(Play);
                                }
        return notify_fail("人齐了哦。\n");
}
int do_da(string str,object me)
{
        int check,i;
        int *winner=({0,0,0,0});
        string ponid;
        mapping who;
        object met;

        if (!me) me=this_player();
        if( check_id(query("id", me),"player") != "");
        else
        {
                command("stare"+query("id", me));
                command("say 这牌局跟你没关系。");
                return 1;
        }
        if (!Playing)
        {
                command("kick"+query("id", me));
                command("say 牌局还没开始呢，您可别拿牌乱丢！");
                return 1;
        }
        tell_object(me,"换谁打牌:"+NowPlayerId[NowPlayer]+"\n");
        if (!str) return notify_fail("指令：da <代码>\n");
        if( query("id", me) != NowPlayerId[NowPlayer] )
        {
                command("hammer"+query("id", me));
                command("say 想偷打牌！作弊啊？");
                return 1;
        }
        if (!Touched)
        {
                command("faint"+query("id", me));
                command("say 您还没摸牌哪！");
                return 1;
        }
        if (Goned==5)
        {
                message_vision("$N说道：这把呀，是"+HIR+"五花合牌"+NOR+"，重新开始吧。\n",this_object());
                Playing=0;
                Count++;
                if (Play==4)
                {
                        for (i=0;i<Play;i++)
                        {
                                met=present(NowPlayerId[i], environment(this_object()));
                                if (!met) met=find_player(NowPlayerId[i]);
                                if (!met);
                                else
                                {
                                        if (!winner=get_mjdata(NowPlayerId[i])) winner=({0,0,0,0});
                                        winner[0]++;
                                        set_mjdata(met,winner);
                                }
                        }
                }
                return 1;
        }
        NO_HU=0;
        HU_F=0;
        NO_GANG=0;
        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        check=do_check_Mj(MjE,str);
        if (check==0) return notify_fail("没有["+str+"]这种代码。\n");
        check=do_check_Mj(who["Mj"],str);
        if (check==0) return notify_fail("您没"+do_check_num(str,0)+"这张牌呀。\n");
        tell_object(me,"你说道："+do_check_num(str,0)+"。\n");
        tell_room(environment(this_object()),me->name()+"说道："+do_check_num(str,0)+"\n",me);
        command("say "+me->name()+"打出了一张"+do_check_num(str,0)+"。\n");
        who["Mj"]=do_delete_Mj(who["Mj"],str,1);
        LastDump=str;
        who["Dump"]+=str;
        LastDumpId=who["Id"];
        Touched=0;
        NowPlayer++;
        NowPlayer%=Play;
        message_vision("$N说道：该"+HIY+NowPlayerId[NowPlayer]+NOR+"摸牌了。\n",this_object());
        if (Auto_Tin)
        {
                ponid=check_id(str,"ting");
                if (ponid!="")
                {
                        me=present(ponid, environment(this_object()));
                        if (!me) me=find_player(ponid);
                        if (!me) return 1;
                        return do_win(str,me);
                }
        }
        if (Auto_Gang)
        {
                ponid=check_id(str,"gang");
                if (ponid!="")
                {
                        me=present(ponid, environment(this_object()));
                        if (!me) me=find_player(ponid);
                        if (!me) return 1;
                        do_gang(str,me);
                }
        }
        if (Auto_Peng)
        {
                ponid=check_id(str,"peng");
                if (ponid!="")
                {
                        me=present(ponid, environment(this_object()));
                        if (!me) me=find_player(ponid);
                        if (!me) return 1;
                        do_peng(str,me);
                }
        }
        if (count==(end-16-Goned))
        {
                Playing=0;
                Count++;
                message_vision("$N说道：这把呀，是"+HIY+"流局"+NOR+"，重新开始吧。\n",this_object());
                str="所剩下的牌只有："+show_mj(List[count..end],2)+"\n";
                tell_room(environment(this_object()),str);
                if (Play==4)
                {
                        for (i=0;i<Play;i++)
                        {
                                met=present(NowPlayerId[i], environment(this_object()));
                                if (!met) met=find_player(NowPlayerId[i]);
                                if (!met);
                                else
                                {
                                        if (!winner=get_mjdata(NowPlayerId[i])) winner=({0,0,0,0});
                                        winner[0]++;
                                        set_mjdata(met,winner);
                                }
                        }
                }
                return 1;
        }
        if (Auto)
        {
                if (NowPlayerId[NowPlayer]==P1Data["Id"]) who=P1Data;
                else if (NowPlayerId[NowPlayer]==P2Data["Id"]) who=P2Data;
                else if (NowPlayerId[NowPlayer]==P3Data["Id"]) who=P3Data;
                else if (NowPlayerId[NowPlayer]==P4Data["Id"]) who=P4Data;
                if (who["Auto"]=="auto")
                {
                        me=present(NowPlayerId[NowPlayer], environment(this_object()));
                        if (!me) me=find_player(NowPlayerId[NowPlayer]);
                        if (!me) return 1;
                        call_out("do_touch",1,"AUTO",me);
                }
        }
        return 1;
}

int do_eat(string str)
{
        int LastDumpMan,i;
        string num1,num2;
        object me=this_player();
        mapping who;

        if (!str || sscanf(str,"%s %s",num1,num2)!=2) return 0;
        if( check_id(query("id", me),"player") != "");
        else
        {
                command("stare"+query("id", me));
                command("say 这把呀，您就边上看着吧。");
                return 1;
        }
        if (!Playing)
        {
                command("say 都还没开始呢。");
                return 1;
        }
        tell_object(me,"换谁摸牌:"+NowPlayerId[NowPlayer]+"\n");
        if( query("id", me) != NowPlayerId[NowPlayer] )
        {
                command("hammer"+query("id", me));
                command("say 没轮到您呢，悠着点儿来吧。");
                return 1;
        }
        if (!LastDump || LastDump=="")
        {
                command("hammer"+query("id", me));
                command("say 摸牌吧。");
                return 1;
        }
        if (Touched)
        {
                command("slap"+query("id", me));
                command("say 打牌啦！");
                return 1;
        }
        if (do_check_eat(num1,num2,LastDump)==0)
        {
                command("crab "+me->name());
                command("say 瞧您那眼神儿，这样也能吃呀。");
                return 1;
        }
        if (num1==num2)
        {
                command("faint "+me->name());
                command("say 相同的牌不能吃。");
                return 1;
        }
        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        LastDumpMan=do_check_Mj(MjE,num1);
        if (LastDumpMan==0)
                return notify_fail("没有["+num1+"]这种代码。\n");
        LastDumpMan=do_check_Mj(MjE,num2);
        if (LastDumpMan==0)
                return notify_fail("没有["+num2+"]这种代码。\n");
        LastDumpMan=do_check_Mj(who["Mj"],num1);
        if (LastDumpMan==0)
                return notify_fail("您没"+do_check_num(num1,0)+"这张牌呀。\n");
        LastDumpMan=do_check_Mj(who["Mj"],num2);
        if (LastDumpMan==0)
                return notify_fail("您没"+do_check_num(num2,0)+"这张牌呀。\n");
        message_vision("\n$N拍出"+HIG+do_check_num(num1,0)+NOR+
                "和"+HIY+do_check_num(num2,0)+NOR+
                "吃下了"+HIR+do_check_num(LastDump,0)+NOR+"。\n\n",me);
        who["Out"]+=num2;
        who["Out"]+=LastDump;
        who["Out"]+=num1;
        who["Mj"]=do_delete_Mj(who["Mj"],num1,1);
        who["Mj"]=do_delete_Mj(who["Mj"],num2,1);
        Touched=1;
        NO_HU=1;
        NO_GANG=1;
        i=0;
        if (who["Show"]=="代码") i=3;
        if (who["Show"]=="color") i=5;
        tell_object(me,show_mj(who["Mj"],i));
        return delete_last_dump(who["Id"]);
}

int do_gang(string str,object me)
{
        int i;
        mapping who;

        if (!me) me=this_player();
        if( check_id(query("id", me),"player") != "");
        else
        {
                command("stare"+query("id", me));
                command("say 这把呀，您就边上看着吧。");
                return 1;
        }
        if (!Playing)
        {
                command("say 都还没开始呢。");
                return 1;
        }
        if( LastDumpId == query("id", me) )
        {
                command("stare"+query("id", me));
                command("say 那张牌可是您自个儿打的。");
                return 1;
        }
        if( Touched && NowPlayerId[NowPlayer] != query("id", me) )
        {
                command("hammer"+query("id", me));
                command("say 别人都还没打牌呢，您杠什么呀。");
                return 1;
        }
        if (!str) str=LastDump;

        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        if (who["Auto"]=="auto") return 1;
        i=do_check_Mj(who["Mj"],str);
        if (i==1)
        {
                if (!Touched) return notify_fail("您还没摸牌呢。\n");
                i=do_check_Mj(who["OutPeng"],str);
                if (!i) return notify_fail("您只有一张不能杠。\n");
                if (NO_GANG) return notify_fail("这样可杠不了。\n");
                message_vision("\n$N说道："+HIB+"木工"+NOR+"～～～\n\n",me);
                who["Mj"]=do_delete_Mj(who["Mj"],str,1);
                sort_data(who["OutPeng"]+=str);
                str=List[end..end+1];
                end-=2;
                Goned++;
                message_vision("\n$N从后面补了一张牌。\n\n",me);
                printf("你补到一张%s\n",do_check_num(str,0));
                i=0;
                if (who["Show"]=="代码") i=3;
                if (who["Show"]=="color") i=5;
                who["Mj"]+=str;
                check_flower(who);
                tell_object(me,show_mj(who["Mj"],i));
                Touched=1;
                return 1;
        }
        if (i < 3)
                return notify_fail("你手中要有三张"+do_check_num(str,0)+"才能杠。\n");
        if (!Touched)
        {
                if (str!=LastDump) return notify_fail("这样可杠不了。\n");
        }
        else if (i < 4)
                        return notify_fail("你手中要有四张"+do_check_num(str,0)+"才能暗杠。\n");
        for (i=0;i<Play;i++)
        {
                if( NowPlayerId[NowPlayer] == query("id", me))break;
                NowPlayer++;
                NowPlayer%=Play;
        }
        who["Mj"]=do_delete_Mj(who["Mj"],str,3);
        if( Touched && NowPlayerId[NowPlayer] == query("id", me) )
        {
                NO_HU=0;
                message_vision("\n$N脸上不禁露出邪恶的笑容：hia hia hia ...\n\n",me);
                who["Mj"]=do_delete_Mj(who["Mj"],str,1);
                for (i=0;i<4;i++) who["Out"]+="xx";
                for (i=0;i<4;i++) who["OutGang"]+=str;
        } else
        {
                NO_HU=1;
                message_vision("\n$N大叫："+do_check_num(str,0)+"～"+HIW+"木工～～～"+NOR+"\n\n",me);
                for (i=0;i<4;i++) who["Out"]+=str;
        }
        str=List[end..end+1];
        end-=2;
        Goned++;
        message_vision("$N从后面补了一张牌。\n",me);
        tell_object(me,"你补到一张"+do_check_num(str,0)+"\n");
        who["Mj"]+=str;
        check_flower(who);
        i=0;
        if (who["Show"]=="代码") i=3;
        if (who["Show"]=="color") i=5;
        tell_object(me,show_mj(who["Mj"],i));
        if (Touched) return 1;
        Touched=1;
        return delete_last_dump(who["Id"]);
}

varargs int do_win(string str,object me)
{
        int i,j;
        int *winner=({0,0,0,0});
        string Mj="";
        mapping who;
        object met;

        if (!me) me=this_player();
        if( check_id(query("id", me),"player") != "");
        else
        {
                command("stare"+query("id", me));
                command("say 这把呀，您就在边上瞧着吧。");
                return 1;
        }
        if (!Playing)
        {
                command("say 都还没开始呢。");
                return 1;
        }
        if( NO_HU || LastDumpId == query("id", me) )
                return notify_fail("这样可不能胡牌。\n");
        if (LastDump==""&&Touched)
                message_vision("\n$N大叫："+HIW+"天～～～胡～～～"+NOR+"\n\n",me);
        else
        {
                tell_room(environment(this_object()),"\n"+me->name()+"大叫："+HIW+"我～胡～啦～"+NOR+"\n\n",me);
                tell_object(me,"\n你大叫："+HIW+"我～胡～啦～"+NOR+"\n\n");
        }
        if( Touched && NowPlayerId[NowPlayer] == query("id", me) )
                message_vision("$N说道：胡家"+me->name()+HIG+"自摸"+NOR+"～～～～～～～"+HIR+"吃红"+NOR+"～～～～～\n",this_object());
        else command("say "+me->name()+"胡了");
        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        if (sizeof(who["OutFlower"]) ==16) i=1;
        else if (sizeof(who["OutFlower"]) ==14&&sizeof(P1Data["OutFlower"]+P2Data["OutFlower"]+P3Data["OutFlower"]+P4Data["OutFlower"])==16) i=1;
                if (!HU_F) i=0;
        if (i)
        {
                Mj+="胡家的花牌是：\n";
                Mj+=show_mj(who["OutFlower"],1);
                if (NowPlayerId[NowPlayer]==who["Id"]) Mj+="胡家花胡自摸\n";
                else
                {
                        if (sizeof(P1Data["OutFlower"])==2) LastDumpId=P1Data["Id"];
                        else if (sizeof(P2Data["OutFlower"])==2) LastDumpId=P2Data["Id"];
                        else if (sizeof(P3Data["OutFlower"])==2) LastDumpId=P3Data["Id"];
                        else if (sizeof(P4Data["OutFlower"])==2) LastDumpId=P4Data["Id"];
                        Mj+="\n花牌放枪者："+HIB+LastDumpId+NOR+"\n";
                }
        } else
        {
                Mj+="胡家的牌是：\n";
                if (who["OutGang"]!="")
                {
                        Mj+="暗杠的有：\n";
                        Mj+=show_mj(who["OutGang"],0);
                }
                Mj+=who["Id"]+":手中的牌有：\n";
                if (!Touched)
                {
                        who["Mj"]+=LastDump;
                        who["Mj"]=sort_data(who["Mj"]);
                        Mj+=show_mj(who["Mj"],0);
                        Mj+="所胡的牌是："+HIR+do_check_num(LastDump,0)+NOR;
                        Mj+="\n放枪者："+HIB+LastDumpId+NOR+"\n";
                } else
                {
                        Mj+=show_mj(who["Mj"],0);
                        if (str) Mj+="所自摸的牌是："+HIR+do_check_num(str,0)+NOR+"\n";
                }
        }
        Playing=0;
        tell_room(environment(this_object()),Mj);
        Tc="";
        if (do_check_win(who["Mj"])==1||i==1)
        {
//算台///////////////////////////////////
                mixed MjT = ([
"@1" : ({ "庄家", 1 }),"@2" : ({ "自摸", 1 }),"@3" : ({ "花牌", 1 }),"@4" : ({ "门清", 1 }),
"@5" : ({ "东风", 1 }),"@6" : ({ "南风", 1 }),"@7" : ({ "西风", 1 }),"@8" : ({ "北风", 1 }),
"@9" : ({ "红中", 1 }),"@0" : ({ "青发", 1 }),"@a" : ({ "白板", 1 }),"@G" : ({ "一丕口", 1 }),
"@b" : ({ "海底摸月", 1 }),"@c" : ({ "海底捞鱼", 1 }),"@d" : ({ "平胡", 2 }),"@e" : ({ "东风东", 2 }),
"@f" : ({ "南风南", 2 }),"@g" : ({ "西风西", 2 }),"@h" : ({ "北风北", 2 }),"@i" : ({ "全求人", 2 }),
"@j" : ({ "三暗刻", 2 }),"@H" : ({ "二丕口", 2 }),"@k" : ({ "三杠子", 2 }),"@B" : ({ "春夏秋冬", 2 }),
"@C" : ({ "梅兰菊竹", 2 }),"@l" : ({ "门清自摸", 3 }),"@m" : ({ "碰碰胡", 4 }),"@n" : ({ "混一色", 4 }),
"@o" : ({ "小三元", 4 }),"@p" : ({ "四暗刻", 6 }),"@q" : ({ "清一色", 8 }),"@r" : ({ "字一色", 8 }),
"@s" : ({ "七对子", 8 }),"@t" : ({ "大三元", 8 }),"@u" : ({ "五暗刻", 8 }),"@F" : ({ "小四喜", 8 }),
"@D" : ({ "七抢一", 8 }),"@E" : ({ "绿一色", 16 }),"@v" : ({ "大四喜", 16 }),"@w" : ({ "天胡", 16 }),
"@x" : ({ "地胡", 16 }),"@y" : ({ "人胡", 16 }),"@z" : ({ "国士无双", 16 }),"@A" : ({ "八仙过海", 16 }),
"@J" : ({ "清老头", 8 }),"@I" : ({ "混老头", 4 }),
]);//H
                get_tc(who);
////////////////
                str="\t\t\t≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n";
                for (i=0;i<sizeof(Tc);i+=2)
                {
                        str+=sprintf("\t\t\t%-12s%8s 台\n",MjT[Tc[i..i+1]][0],chinese_number(MjT[Tc[i..i+1]][1]));
                        j+=MjT[Tc[i..i+1]][1];
                }
                if (Count)
                {
                        str+=sprintf("\t\t\t%-12s%8s 台\n","连"+chinese_number(Count)+"拉"+chinese_number(Count),chinese_number(Count*2));
                        j+=Count*2;
                }
                str+=sprintf("\t\t\t%20s\n","总台数:"+chinese_number(j+5)+" 台");
                str+="\t\t\t≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n";
                tell_room(environment(this_player()),str);
/////////////
                if (!Touched)
                {
                        if (Play==4)
                        {
                                if( !winner=get_mjdata(query("id", me)))winner=({0,0,0,0});
                                winner[1]+=j;
                                set_mjdata(me,winner);
                                met=present(LastDumpId, environment(this_object()));
                                if (!met) met=find_player(LastDumpId);
                                if (!met);
                                else
                                {
                                        if (!winner=get_mjdata(LastDumpId)) winner=({0,0,0,0});
                                        winner[1]-=j; //战绩
                                        winner[3]++; //放枪
                                        set_mjdata(met,winner);
                                }
                                for (i=0;i<Play;i++)
                                {
                                        met=present(NowPlayerId[i], environment(this_object()));
                                        if (!met) met=find_player(NowPlayerId[i]);
                                        if (!met);
                                        else
                                        {
                                                if (!winner=get_mjdata(NowPlayerId[i]))
                                                        winner=({0,0,0,0});
                                                winner[0]++; //局数
                                                set_mjdata(met,winner);
                                        }
                                }
                        }
                } else
                {
                        if (Play==4)
                        {
                                if( !winner=get_mjdata(query("id", me)))winner=({0,0,0,0});
                                winner[0]++;
                                winner[1]+=(j*3);
                                winner[2]++;
                                set_mjdata(me,winner);
                                for (i=0;i<Play;i++)
                                {
                                        if( NowPlayerId[i] == query("id", me))continue;
                                        met=present(NowPlayerId[i], environment(this_object()));
                                        if (!met) met=find_player(NowPlayerId[i]);
                                        if (!met);
                                        else
                                        {
                                                if (!winner=get_mjdata(NowPlayerId[i]))
                                                        winner=({0,0,0,0});
                                                winner[0]++;
                                                winner[1]-=j;
                                                set_mjdata(met,winner);
                                        }
                                }
                        }
                }
                if (NowPlayerId[0]==who["Id"]) Count++;
                else
                {
                        Times++;
                        Count=0;
                }
        } else
        {
                command("sigh "+who["Id"]);
                message_vision("$N说道：玩家 ["+HIR+who["Id"]+HIG+"] 言乍～ 古月～～～"+NOR+"。\n",this_object());
                Times++;
                Count=0;
                if (Play==4)
                {
                        if( !winner=get_mjdata(query("id", me)))winner=({0,0,0,0});
                        if (NowPlayerId[NowPlayer]==who["Id"]&&Touched)
                        {
                                if (who["Out"]==""&&who["OutPeng"]=="")
                                {
                                        winner[1]-=24;
                                        j=-24;
                                } else
                                {
                                        winner[1]-=18;
                                        j=-18;
                                }
                        } else
                        {
                                if (who["Out"]==""&&who["OutPeng"]=="")
                                {
                                        winner[1]-=6;
                                        j=-6;
                                } else
                                {
                                        winner[1]-=5;
                                        j=-5;
                                }
                        }
////////////////
                        str="\t\t\t≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n";
                        str+=sprintf("\t\t\t%-12s%8s 台\n","言乍古月",chinese_number(j));
                        str+=sprintf("\t\t\t%20s\n","总台数:"+chinese_number(j+5)+" 台");
                        str+="\t\t\t≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n";
                        tell_room(environment(this_player()),str);
/////////////
                        set_mjdata(me,winner);
                        for (i=0;i<Play;i++)
                        {
                                met=present(NowPlayerId[i], environment(this_object()));
                                if (!met) met=find_player(NowPlayerId[i]);
                                if (!met);
                                else
                                {
                                        if (!winner=get_mjdata(NowPlayerId[i]))
                                                winner=({0,0,0,0});
                                        winner[0]++;
                                        set_mjdata(met,winner);
                                }
                        }
                }
        }
        Mj="\n[0;1;36;46m  ";
        for (i=0; i<26; i++) Mj+="  ";
        Mj+="[1;36;46m  [0m\n";
        Mj+="[1;36;46m  [0;36m      "+HIW+"中[0m文名字  [1m已[0m玩局数  [1m总[0m战绩  [1m自[0m摸次数  [1m放[0m枪次数[1;36;46m  [0m\n";
        for (i=0;i<Play;i++)
        {
                if (Play==4) winner=get_mjdata(NowPlayerId[i]);
                Mj+=sprintf("[1;36;46m  [0;36m  [1;37m%12s  [33m%8d  [35m%6d  [32m%8d  [34m%8d[1;36;46m  [0m\n", NowPlayerId[i],winner[0],winner[1],winner[2],winner[3]);
        }
        Mj+="[1;36;46m  ";
        for (i=0; i<26; i++) Mj+="  ";
        Mj+="[46m＼[0m\n";
        if (Play==4) tell_room(environment(this_object()),Mj);
        return wash_mj(Play);
}

int do_check_win(string str)
{
        int size=strlen(str),i,check;
        int t,k,W,T,S,Sp;
        string tempW="",tempT="",tempS="",tempB="";
        string Special="1w9w1s9s1t9teasowenojofaba";

        K=0;
        if (size > 33)
        {
                if (do_check_Mj(str,"ea")&&do_check_Mj(str,"so")&&do_check_Mj(str,"we")&&do_check_Mj(str,"no")&&
                do_check_Mj(str,"jo")&&do_check_Mj(str,"fa")&&do_check_Mj(str,"ba")&&
                do_check_Mj(str,"1w")&&do_check_Mj(str,"9w")&&do_check_Mj(str,"1s")&&
                do_check_Mj(str,"9s")&&do_check_Mj(str,"1t")&&do_check_Mj(str,"9t"))
                {
                        //先删掉13只
                        for (i=0;i<sizeof(Special);i+=2)
                        {
                                if (do_check_Mj(str,Special[i..i+1]))
                                {
                                        str=do_delete_Mj(str,Special[i..i+1],1);
                                }
                        }
                        //查还有没13么中的牌只
                        for (i=0;i<sizeof(Special);i+=2)
                        {
                                if (do_check_Mj(str,Special[i..i+1]))
                                {
                                        Sp++;
                                }
                        }
                        if (Sp==1)
                        {
                                for (i=0;i<sizeof(Special);i+=2)
                                {
                                        if (do_check_Mj(str,Special[i..i+1]))
                                        {
                                                str=do_delete_Mj(str,Special[i..i+1],1);
                                                t++;
                                                Tc+="@z";//13么
                                        }
                                }
                        }
                        else if (Sp==2)
                                {
                                        for (i=0;i<sizeof(str);i+=2)
                                        {
                                                if (do_check_Mj(str,str[i..i+1])==2)
                                                {
                                                        str=do_delete_Mj(str,str[i..i+1],1);
                                                        Sp=0;
                                                        t++;
                                                }
                                        }
                                        if (Sp!=0)
                                        {
                                                if (str[0..1]+1==str[2..3])
                                                {
                                                        str=do_delete_Mj(str,str[6..7],1);
                                                        t++;
                                                } else
                                                {
                                                        str=do_delete_Mj(str,str[0..1],1);
                                                        t++;
                                                }
                                        }
                                }
                } else
                {
                        for (i=0;i<sizeof(str);i+=2)
                        {
                                if (do_check_Mj(str,str[i..i+1])==2) Sp++;
                                else if (do_check_Mj(str,str[i..i+1])==3) check++;
                                else if (do_check_Mj(str,str[i..i+1])==4) Sp++;
                        }
                        if (Sp==14&&check==3)
                        {
                                for (i=0;i<sizeof(str);i+=2)
                                {
                                        if (do_check_Mj(str,str[i..i+1])==2)
                                        {
                                                str=do_delete_Mj(str,str[i..i+1],2);
                                                i=-2;
                                        }
                                        else if (do_check_Mj(str,str[i..i+1])==4)
                                                {
                                                        str=do_delete_Mj(str,str[i..i+1],4);
                                                        i=-2;
                                                }
                                                else if (do_check_Mj(str,str[i..i+1])==3) t++;
                                }
                                t=1;
                                Tc+="@s";//7对子
                        }
                }
        }
        while(size--)
        {
                size--;
                if (do_check_num(str[size..size+1],1) < 10)
                        tempW+=str[size..size+1];
                else if (do_check_num(str[size..size+1],1) < 19)
                                tempT+=str[size..size+1];
                        else if (do_check_num(str[size..size+1],1) < 28)
                                        tempS+=str[size..size+1];
                                else tempB+=str[size..size+1];
        }
        if (tempB!="")
        {
                for (i=0;i<strlen(tempB);i+=2)
                {//
                        check=do_check_Mj(tempB,tempB[i..i+1]);
                        if (check==1) return 0;
                        else if (check==2)
                                {
                                        tempB=do_delete_Mj(tempB,tempB[i..i+1],2);
                                        t++;
                                        i=-2;
                                } else if (check==3)
                                        {
                                                tempB=do_delete_Mj(tempB,tempB[i..i+1],3);
                                                K++;
                                                i=-2;
                                        }
                }//
        }
        if (tempW!="") W=check_hu(tempW);
        if (tempT!="") T=check_hu(tempT);
        if (tempS!="") S=check_hu(tempS);
        if (K==3) Tc+="@j";//三暗刻
        else if (K==4) Tc+="@p";//四暗刻
        else if (K==5) Tc+="@u";//五暗刻
        if (W+T+S+t==1) return 1;
        return 0;
}

int check_hu(string strW)
{
        int i,j,check;
        int k,t;
        int A,B,C,D,E,F;
        for (i=0;i<sizeof(strW);i+=2)
        {//再把顺子删掉
                A=do_check_num(strW[i..i+1],2);
                B=do_check_num(strW[i+2..i+3],2);
                C=do_check_num(strW[i+4..i+5],2);
                D=do_check_num(strW[i+6..i+7],2);
                E=do_check_num(strW[i+8..i+9],2);
                F=do_check_num(strW[i+10..i+11],2);
                if (sizeof(strW) > 11 &&do_check_num(strW[i-2..i-1],2)!=A&&A+1==B&&B==C&&C+1==D&&D==E&&E+1==F ||do_check_num(strW[i-2..i-1],2)!=A&&A==B&&B+1==C&&C==D&&D+1==E&&E==F)
                {
                        if (A==B&&B+1==C&&C==D&&D+1==E&&E==F)
                        {
                                if (do_check_Mj(Tc,"@G")==1)
                                {
                                        Tc=do_delete_Mj(Tc,"@H",1);
                                        Tc+="@H";
                                } else Tc+="@G";
                        }
                        for (j=0;j<6;j++)
                        {  //删掉顺子1 22 33 4 && 22 33 44
                                strW=do_delete_Mj(strW,strW[i..i+1],1);
                        }
                        i=-2;
                }
                else if (A+1==B&&B==C&&C==D&&D==E&&E+1==F)
                        {
                                for (j=0;j<2;j++)
                                {  //删掉顺子1 2 2 2 2 3
                                        strW=do_delete_Mj(strW,strW[i..i+1],1);
                                }
                                strW=do_delete_Mj(strW,strW[i+6..i+7],1);
                                i=-2;
                        }
                        else if (sizeof(strW) > 9 && A+1==B&&B==C&&C==D&&D+1==E)
                                {  //删掉顺子12223中的1 2 3
                                        strW=do_delete_Mj(strW,strW[i..i+1],1);
                                        strW=do_delete_Mj(strW,strW[i..i+1],1);
                                        strW=do_delete_Mj(strW,strW[i+4..i+5],1);
                                        i=-2;
                                }
                                else if (sizeof(strW) > 9 && A==B&&B+1==C&&C+1==D&&D+1==E)
                                        {
                                                for (j=0;j<3;j++)
                                                {        //删掉顺子11234中的2 3 4
                                                        strW=do_delete_Mj(strW,strW[i+4..i+5],1);
                                                }
                                                i=-2;
                                        }
                                        else if (sizeof(strW) > 5 && A+1==B&&B+1==C)
                                                {
                                                        for (j=0;j<3;j++)
                                                        {        //删掉顺子123中的1 2 3
                                                                strW=do_delete_Mj(strW,strW[i..i+1],1);
                                                        }
                                                        i=-2;
                                                }
        }

        if (sizeof(strW) > 5)
        {
                for (i=0;i<sizeof(strW);i+=2)
                {  //再把刻删掉
                        check=do_check_Mj(strW,strW[i..i+1]);
                        if (check==3)
                        {
                                K++;
                                strW=do_delete_Mj(strW,strW[i..i+1],3);
                                i=-2;
                        }
                }
        }
        for (i=0;i<sizeof(strW);i+=2)
        {  //再把对删掉
                check=do_check_Mj(strW,strW[i..i+1]);
                if (check==2)
                {
                        t++;
                        strW=do_delete_Mj(strW,strW[i..i+1],2);
                        i=-2;
                }
        }
        if (strW!="") return 99;
        return t;
}

int do_touch(string str,object me)
{
        int i,check;
        mapping who;

        if (!me) me=this_player();
        if( check_id(query("id", me),"player") != "");
        else
        {
                command("stare"+query("id", me));
                command("say 这把呀，您就在一边儿瞧着吧。");
                return 1;
        }
        if (!Playing)
        {
                command("say 都还没开始呢，您摸牌藏起来干嘛呀。");
                return 1;
        }
        tell_object(me,"换谁摸牌:"+NowPlayerId[NowPlayer]+"\n");
        if( query("id", me) != NowPlayerId[NowPlayer] )
        {
                command("hammer"+query("id", me));
                command("say 想偷牌呀，没那麽容易哦。");
                return 1;
        }
        if (Touched)
        {
                command("slap"+query("id", me));
                command("say 打牌啦！别磨磨蹭蹭的。");
                return 1;
        }
        NO_HU=0;
        NO_GANG=0;
        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        if (who["Auto"]=="auto")
        {
                if (str=="AUTO");
                else
                {
                        write("设定自动听牌后、不可自己摸牌。\n");
                        return 1;
                }
        }
        Touched=1;
        str=List[count..count+1];
        count+=2;
        tell_room(environment(this_object()),me->name()+"摸了一张牌。\n",me);
        tell_object(me,"你摸了一张牌。\n");
        tell_object(me,"你摸到一张"+do_check_num(str,0)+"。\n");
        if (who["Auto"]=="auto")
        {
                if (do_check_num(str,1) > 34)
                {
                        for (i=0;i<1;i++)
                        {
                                who["OutFlower"]+=str;
                                HU_F=1;
                                tell_room(environment(this_object()),me->name()+"说道："+HIB+"花牌"+NOR+"补花。\n\n"+me->name()+"往后面补了一张牌。\n",me);
                                tell_object(me,"你说道："+HIB+"花牌"+NOR+"补花。\n\n你往后面补了一张牌。\n");
                                str=List[end..end+1];
                                end-=2;
                                tell_object(me,"你摸到了一张"+do_check_num(str,0)+"。\n");
                                if (do_check_num(str,1) > 34) i--;
                        }
                }
                check=do_check_Mj(who["AutoTin"],str);
                if (check!=0)
                {
                        who["Mj"]+=str;
                        who["Mj"]=sort_data(who["Mj"]);
                        return do_win(str,me);
                }
                call_out("do_da",0,str,me);
        }
        who["Mj"]+=str;
        check_flower(who);
        i=0;
        if (who["Show"]=="代码") i=3;
        if (who["Show"]=="color") i=5;
        tell_object(me,show_mj(who["Mj"],i));
        return 1;
}

int do_peng(string str,object me)
{
        int i;
        mapping who;

        if (!me) me=this_player();
        if( check_id(query("id", me),"player") != "");
        else
        {
                command("stare"+query("id", me));
                command("say 这把呀，您就在一边儿瞧着吧。");
                return 1;
        }
        if (!Playing)
        {
                command("die"+query("id", me));
                command("say 都还没开始呢，碰你个头啊。");
                return 1;
        }
        if (Touched)
        {
                command("hammer"+query("id", me));
                command("say 别人没打牌您可怎麽碰哟。");
                return 1;
        }
        if( LastDumpId == query("id", me) )
        {
                command("stare"+query("id", me));
                command("say 那张牌可是您自个儿打的。");
                return 1;
        }
        if (!str) str=LastDump;
        else if (str!=LastDump)
                        return notify_fail("那张"+do_check_num(str,0)+"已经过期了。\n");
        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        if (who["Auto"]=="auto") return 1;
        i=do_check_Mj(who["Mj"],str);
        if (i==0)
                return notify_fail("你没"+do_check_num(str,0)+"这张牌要怎麽碰。\n");
        if (i < 2)
                return notify_fail("你手中要有两张"+do_check_num(str,0)+"才能碰。\n");

        message_vision("\n$N大叫："+do_check_num(str,0)+"～"+HIM+"石並～～～"+NOR+"\n\n",me);
        for (i=0;i<Play;i++)
        {
                if( NowPlayerId[NowPlayer] == query("id", me))break;
                NowPlayer++;
                NowPlayer%=Play;
        }
        for (i=0;i<3;i++) who["OutPeng"]+=str;
        who["Mj"]=do_delete_Mj(who["Mj"],str,2);
        who["AutoPeng"]=do_delete_Mj(who["AutoPeng"],str,1);
        NO_HU=1;
        NO_GANG=1;
        Touched=1;
        i=0;
        if (who["Show"]=="代码") i=3;
        if (who["Show"]=="color") i=5;
        tell_object(me,show_mj(who["Mj"],i));
        return delete_last_dump(who["Id"]);
}

int do_restart(string str)
{
        object me=this_player();
        if( query("id", me) == "guest")return 0;
        if (str!="mj")
        {
                if( check_id(query("id", me),"player") != "");
                else
                {
                        command("stare"+query("id", me));
                        command("say 这把呀，您就在一边儿瞧着吧。");
                        return 1;
                }
        }
        message_vision("$N把牌局重新设定。\n",me);
        message_vision("$N说道：牌局重新设定请用"+HIR+" sit "+NOR+"加入牌局。\n",this_object());
        NowPlayerId[0]="";
        NowPlayerId[1]="";
        NowPlayerId[2]="";
        NowPlayerId[3]="";
        P1Data["Id"]="";
        P2Data["Id"]="";
        P3Data["Id"]="";
        P4Data["Id"]="";
        Count=0;
        LookP ="";
        Play=START;
        Times=START;
        end=END;
        count=START;
        Playing=START;
        return 1;
}

int wash_mj(int amount)
{
        int i,x;
        string str,countstr="";
        mixed *X,MjE_Data = ([
"1w" : 0,"2w" : 0,"3w" : 0,"4w" : 0,"5w" : 0,"6w" : 0,"7w" : 0,"8w" : 0,"9w" :0,
"1s" : 0,"2s" : 0,"3s" : 0,"4s" : 0,"5s" : 0,"6s" : 0,"7s" : 0,"8s" : 0,"9s" :0,
"1t" : 0,"2t" : 0,"3t" : 0,"4t" : 0,"5t" : 0,"6t" : 0,"7t" : 0,"8t" : 0,"9t" :0,
"ea" : 0,"so" : 0,"we" : 0,"no" : 0,"jo" : 0,"fa" : 0,"ba" : 0,
"f1" : 0,"f2" : 0,"f3" : 0,"f4" : 0,"f5" : 0,"f6" : 0,"f7" : 0,"f8" : 0
]);
        if (!Play)
        {
                command("say 都没人玩儿，要我白洗牌呀？门儿都没有。");
                return 1;
        }
        if (Playing)
        {
                command("say 那几位正打着呢。");
                return 1;
        }
        command("say 我帮着洗牌，待会儿谁胡我可要吃红哦 :)");
        if (Play<4) command("say 都没凑齐四个，咱就不计分了。");
        P1Data["Mj"]="";
        P1Data["OutGang"]="";
        P1Data["Out"]="";
        P1Data["OutPeng"]="";
        P1Data["OutFlower"]="";
        P1Data["Auto"]="";
        P1Data["AutoTin"]="";
        P1Data["AutoGang"]="";
        P1Data["AutoPeng"]="";
        P1Data["Dump"]="";

        P2Data["Mj"]="";
        P2Data["OutGang"]="";
        P2Data["Out"]="";
        P2Data["OutPeng"]="";
        P2Data["OutFlower"]="";
        P2Data["Auto"]="";
        P2Data["AutoTin"]="";
        P2Data["AutoGang"]="";
        P2Data["AutoPeng"]="";
        P2Data["Dump"]="";

        P3Data["Mj"]="";
        P3Data["OutGang"]="";
        P3Data["Out"]="";
        P3Data["OutPeng"]="";
        P3Data["OutFlower"]="";
        P3Data["Auto"]="";
        P3Data["AutoTin"]="";
        P3Data["AutoGang"]="";
        P3Data["AutoPeng"]="";
        P3Data["Dump"]="";

        P4Data["Mj"]="";
        P4Data["OutGang"]="";
        P4Data["Out"]="";
        P4Data["OutPeng"]="";
        P4Data["OutFlower"]="";
        P4Data["Auto"]="";
        P4Data["AutoTin"]="";
        P4Data["AutoGang"]="";
        P4Data["AutoPeng"]="";
        P4Data["Dump"]="";

        end=END;
        NO_HU=START;
        NO_GANG=START;
        count=START;
        Playing=START;
        List="";
        NowPlayer=START;
        Touched=START;
        Auto=START;
        Auto_Tin=START;
        Auto_Gang=START;
        Auto_Peng=START;
        Goned=START;
        LastDump="";
        LastDumpId="";
        X = keys(MjE_Data);
        for (i=0;i<144;i++)
        {
                x = random(sizeof(X));
                if (X[x]=="f1"||X[x]=="f2"||X[x]=="f3"||X[x]=="f4"|| X[x]=="f5"||X[x]=="f6"||X[x]=="f7"||X[x]=="f8")
                {
                        if (MjE_Data[X[x]] < 1)
                        {
                                MjE_Data[X[x]] = MjE_Data[X[x]] + 1;
                                List += X[x];
                        } else i--;
                } else
                {
                        if (MjE_Data[X[x]] < 4)
                        {
                                MjE_Data[X[x]] = MjE_Data[X[x]] + 1;
                                List += X[x];
                        } else i--;
                }
        }

//        for (i=0;i<sizeof(X);i++) printf("%s=%d ",X[i],MjE_Data[X[i]]);
        command("say 嗯，好啦，可以开始了。来吧！");
        if (Count) countstr="[连庄"+chinese_number(Count)+"]";
        if (!Times);
        else
        {
                if (Count);
                else
                {
                        str=NowPlayerId[0];
                        if (Play>1) NowPlayerId[0]=NowPlayerId[1];
                        if (Play>2) NowPlayerId[1]=NowPlayerId[2];
                        if (Play>3) NowPlayerId[2]=NowPlayerId[3];
                        NowPlayerId[Play-1]=str;
                }
        }
        if (Times/Play == 4) Times=0;
        if (Times/Play == 3) str=HIW+"北风"+NOR;
        if (Times/Play == 2) str=HIY+"西风"+NOR;
        if (Times/Play == 1) str=HIR+"南风"+NOR;
        if (Times/Play == 0) str=HIG+"东风"+NOR;
        i=Times;
        i%=Play;
        i++;
        message_vision("["+str+chinese_number(i)+"]牌局开始：庄家"+HIY+NowPlayerId[0]+HIR+countstr+NOR+"掷出骰子"+ "["+HIG+chinese_number(i=3+random(16))+NOR+ "]点。\n",this_object());

        //玩家取牌一次取16只:Q
        if (Play>0) P1Data["Mj"]=List[0..31];
        if (Play>1) P2Data["Mj"]=List[32..63];
        if (Play>2) P3Data["Mj"]=List[64..95];
        if (Play>3) P4Data["Mj"]=List[96..127];
        count=(Play*2*16);
        if (Play>0) check_flower(P1Data);
        if (Play>1) check_flower(P2Data);
        if (Play>2) check_flower(P3Data);
        if (Play>3) check_flower(P4Data);
        Playing=1;
        message_vision("$N说道：庄家"+HIY+NowPlayerId[0]+NOR+"请开门牌。\n",this_object());
        return 1;
}

int do_setmj(string str)
{
        int check;
        string numstr;
        mapping who;
        object me=this_player();

        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        else return 1;
        if (!str)
        {
                numstr=this_object()->name()+"偷偷告诉你：您设定了这些——\n";
                if (who["AutoTin"]!="") numstr+="遇到"+HIB+show_mj(who["AutoTin"],2)+NOR+"会自动"+HIB+"[胡牌]"+NOR+"。\n";
                if (who["AutoGang"]!="") numstr+="遇到"+HIY+show_mj(who["AutoGang"],2)+NOR+"会自动"+HIY+"[杠牌]"+NOR+"。\n";
                if (who["AutoPeng"]!="") numstr+="遇到"+HIG+show_mj(who["AutoPeng"],2)+NOR+"会自动"+HIG+"[碰牌]"+NOR+"。\n";
                if (who["Show"]=="代码")         numstr+="显示方式为"+HIY+"[代码]"+NOR+"方式。\n";
                if (who["Show"]=="color")        numstr+="显示方式为"+HIG+"[彩色]"+NOR+"。\n";
                if (who["Auto"]=="auto")         numstr+="你设定"+HIR+"[自动听牌]"+NOR+"。\n";
                if (who["AutoTin"]==""&&who["AutoGang"]==""&&who["AutoPeng"]==""&&who["Show"]==""&&who["Auto"]=="") numstr+="你没有任何设定。\n";
                tell_room(environment(me),this_object()->name()+"凑近"+me->name()+"耳边嘀咕了半天。\n",me);
                tell_object(me,numstr);
                return 1;
        }
        if (sscanf(str,"%s %s",str,numstr)!=2) return notify_fail("指令：setmj <ting>&<gang>&<peng> <代码>\n");
        if (str=="ting")
        {
                if (numstr=="none")
                {
                        who["AutoTin"]="";
                        return notify_fail("你取消自动胡牌设定。\n");
                }
                check=do_check_Mj(MjE,numstr);
                if (check!=1) return notify_fail("没有["+numstr+"]这种牌。\n");
                check=do_check_Mj(who["AutoTin"],numstr);
                if (check)
                {
                        who["AutoTin"]=do_delete_Mj(who["AutoTin"],numstr,1);
                        return notify_fail("你"+HIR+"删掉了"+NOR+"遇到"+do_check_num(numstr,0)+"会自动胡牌的设定。\n");
                }
                who["AutoTin"]+=numstr;
                Auto_Tin=1;
                write("你设定遇到"+do_check_num(numstr,0)+"时会自动胡牌。\n");
                return 1;
        }
        else if (str=="gang")
                {
                        if (numstr=="none")
                        {
                                who["AutoGang"]="";
                                return notify_fail("你取消自动杠牌设定。\n");
                        }
                        check=do_check_Mj(who["Mj"],numstr);
                        if (check==0)
                                return notify_fail("你没"+do_check_num(numstr,0)+"这张牌。\n");
                        if (check < 3)
                                return notify_fail("你手中要有三张"+do_check_num(numstr,0)+"才能设定杠此牌。\n");
                        check=do_check_Mj(who["AutoGang"],numstr);
                        if (check)
                        {
                                who["AutoGang"]=do_delete_Mj(who["AutoGang"],numstr,1);
                                return notify_fail("你"+HIR+"删掉了"+NOR+"遇到"+do_check_num(numstr,0)+"会自动杠牌的设定。\n");
                        }
                        who["AutoGang"]+=numstr;
                        Auto_Gang=1;
                        write("你设定遇到"+do_check_num(numstr,0)+"时会自动杠牌。\n");
                        return 1;
                }
                else if (str=="peng")
                        {
                                if (numstr=="none")
                                {
                                        who["AutoPeng"]="";
                                        return notify_fail("你取消自动碰牌设定。\n");
                                }
                                check=do_check_Mj(who["Mj"],numstr);
                                if (check==0)
                                        return notify_fail("你没"+do_check_num(numstr,0)+"这张牌。\n");
                                if (check < 2)
                                        return notify_fail("你手中要有两张"+do_check_num(numstr,0)+"才能设定碰此牌。\n");
                                check=do_check_Mj(who["AutoPeng"],numstr);
                                if (check)
                                {
                                        who["AutoPeng"]=do_delete_Mj(who["AutoPeng"],numstr,1);
                                        return notify_fail("你"+HIR+"删掉了"+NOR+"遇到"+do_check_num(numstr,0)+"会自动碰牌的设定。\n");
                                }
                                who["AutoPeng"]+=numstr;
                                Auto_Peng=1;
                                write("你设定遇到"+do_check_num(numstr,0)+"时会自动碰牌。\n");
                                return 1;
                        }
                        else if (str=="show")
                                {
                                        if (numstr=="none"||numstr=="1")
                                        {
                                                who["Show"]="";
                                                return notify_fail("你取消显示设定。\n");
                                        }

                                        if (numstr=="代码"||numstr=="3")
                                        {
                                                numstr="代码";
                                                write("你设定只显示代码。\n");
                                        }
                                        else if (numstr=="color"||numstr=="2")
                                                {
                                                        numstr="color";
                                                        write("你设定彩色显示。\n");
                                                }
                                                else return 1;
                                        who["Show"]=numstr;
                                        return 1;
                                }
                                else if (str=="auto")
                                        {
                                                if (numstr=="none")
                                                {
                                                        return notify_fail("不能取消自动听牌，要是设定错误等着诈胡吧!!:>。\n");
                                                }
                                                if (who["AutoTin"]=="")
                                                        return notify_fail("请先设定要听的牌。\n");
                                                if (!Touched)
                                                        return notify_fail("请先摸牌再做此设定。\n");
                                                if (numstr=="ting")
                                                        write("你设定自动听牌。\n");
                                                else return 1;
                                                message_vision("\n$N大叫一声："+HIW+"我听啦～～～"+NOR+"\n\n",me);
                                                Auto=1;
                                                who["Auto"]="auto";
                                                return 1;
                                        }
        else return notify_fail("没有这种设定。\n");
}

int do_check_eat(string num1,string num2,string LastDump)
{
        int A,B,C;
        A=do_check_num(num1,1);
        B=do_check_num(num2,1);
        C=do_check_num(LastDump,1);
        if (A<10)
        {
                if (B>10||C>10) return 0;
        }
        else if (A<19&&A>10)
                {
                        if (B>19||C>19&&B<10||C<10) return 0;
                }
                else if (A<28&&A>19)
                        {
                                if (B<19||C<19) return 0;
                        }
        A=do_check_num(num1,2);
        B=do_check_num(num2,2);
        C=do_check_num(LastDump,2);

        if (A > 9 || B > 9 || C > 9) return 0;
        if ((A+B)%2!=0)
        {
                if (A > B)
                {
                        if (C==(A+1) || C==(A-2)) return 1;
                } else
                {
                        if (C==(B+1) || C==(B-2)) return 1;
                }
                return 0;
        } else
        {
                if (A > B)
                {
                        if (C==(A-1) || C==(B+1)) return 1;
                } else
                {
                        if (C==(B-1) || C==(A+1)) return 1;
                }
                return 0;
        }
}

string show_mj(string str,int flag)
{
        string Mj="",Mj1="";
        int size=strlen(str)+2,a,b;
        if (!str||str=="") return "";
        if (flag!=3)
        {
                while(size--)
                {
                        size--;
                        Mj+=do_check_num(str[size..size+1],0);
                }
                if (flag==2) Mj1=Mj;
                else
                {
                        size=strlen(Mj);
                        Mj1="┌";
                        for (a=0;a<(size/2)-1;a++)
                        {
                                if (a%2==0) Mj1+="--";
                                else Mj1+="┬";
                        }
                        Mj1+="┐\n│";

                        for (a=0;a<size-1;a++)
                        {
                                if (flag==5 || flag==6)
                                {
                                        if (Mj[a+2..a+3]=="万") Mj1+=HIR;
                                        else if (Mj[a+2..a+3]=="筒") Mj1+=HIC;
                                        else if (Mj[a+2..a+3]=="索") Mj1+=HIG;
                                        else if (Mj[a+2..a+3]=="风") Mj1+=HIM;
                                        else if (Mj[a+2..a+3]=="中") Mj1+=HIR;
                                        else if (Mj[a+2..a+3]=="发") Mj1+=HIG;
                                        else if (Mj[a+2..a+3]=="板") Mj1+=HIW;
                                        else if (Mj[a+2..a+3]=="春" || Mj[a+2..a+3]=="夏" || Mj[a+2..a+3]=="秋" || Mj[a+2..a+3]=="冬") Mj1+=HIR;
                                        else if (Mj[a+2..a+3]=="梅" || Mj[a+2..a+3]=="兰" || Mj[a+2..a+3]=="竹" || Mj[a+2..a+3]=="菊") Mj1+="[1;30m";
                                }
                                Mj1+=Mj[a..a+1];
                                a++;a++;a++;
                                Mj1+=NOR+"│";
                        }
                        Mj1+="\n│";
                        for (a=2;a<size;a++)
                        {
                                if (flag==5 || flag==6)
                                {
                                        if (Mj[a..a+1]=="万") Mj1+=RED;
                                        else if (Mj[a..a+1]=="索") Mj1+=GRN;
                                        else if (Mj[a..a+1]=="筒") Mj1+=CYN;
                                        else if (Mj[a..a+1]=="风") Mj1+=MAG;
                                        else if (Mj[a..a+1]=="中") Mj1+=HIR;
                                        else if (Mj[a..a+1]=="发") Mj1+=HIG;
                                        else if (Mj[a..a+1]=="白") Mj1+=HIW;
                                        else if (Mj[a..a+1]=="春") Mj1+=HIG;
                                        else if (Mj[a..a+1]=="夏") Mj1+=HIB;
                                        else if (Mj[a..a+1]=="秋") Mj1+=HIY;
                                        else if (Mj[a..a+1]=="冬") Mj1+=HIW;
                                        else if (Mj[a..a+1]=="梅") Mj1+=HIW;
                                        else if (Mj[a..a+1]=="兰") Mj1+=HIR;
                                        else if (Mj[a..a+1]=="竹") Mj1+=HIG;
                                        else if (Mj[a..a+1]=="菊") Mj1+=HIY;
                                }
                                Mj1+=Mj[a..a+1];
                                a++;a++;a++;
                                Mj1+=NOR+"│";
                        }
                        Mj1+="\n└";
                        for (a=(size/2)-1;a>0;a--)
                        {
                                if (a%2!=0)
                                {
                                        if (flag==0 || flag==5) Mj1+=str[a-1..a];
                                        else Mj1+="--";
                                }
                                else Mj1+="┴";
                        }
                        Mj1+="┘\n";
                }
                return Mj1;
        } else
        {
                size*=2;
                for (a=(size/2)-1;a>0;a--)
                {
                        if (a%2!=0) Mj1+=str[a-1..a];
                        else Mj1+=" ";
                }
                Mj1+="\n";
        }
        return Mj1;
}

string check_id(string str,string kind)
{
        int check,i;
        if (!str) return "";
        if (kind=="ting")
        {
                check=NowPlayer;
                for (i=0;i<Play-1;i++)
                {
                        if (NowPlayerId[check]==P1Data["Id"] && do_check_Mj(P1Data["AutoTin"],str)!=0) return P1Data["Id"];
                        if (NowPlayerId[check]==P2Data["Id"] && do_check_Mj(P2Data["AutoTin"],str)!=0) return P2Data["Id"];
                        if (NowPlayerId[check]==P3Data["Id"] && do_check_Mj(P3Data["AutoTin"],str)!=0) return P3Data["Id"];
                        if (NowPlayerId[check]==P4Data["Id"] && do_check_Mj(P4Data["AutoTin"],str)!=0) return P4Data["Id"];
                        check++;
                        check%=Play;
                }
                return "";
        }
        if (kind=="gang")
        {
                check=do_check_Mj(P1Data["AutoGang"],str);
                if (check!=0)
                {
                        check=do_check_Mj(P1Data["Mj"],str);
                        if (check < 3) return "";
                        else return P1Data["Id"];
                }
                check=do_check_Mj(P2Data["AutoGang"],str);
                if (check!=0)
                {
                        check=do_check_Mj(P2Data["Mj"],str);
                        if (check < 3) return "";
                        else return P2Data["Id"];
                }
                check=do_check_Mj(P3Data["AutoGang"],str);
                if (check!=0)
                {
                        check=do_check_Mj(P3Data["Mj"],str);
                        if (check < 3) return "";
                        else return P3Data["Id"];
                }
                check=do_check_Mj(P4Data["AutoGang"],str);
                if (check!=0)
                {
                        check=do_check_Mj(P4Data["Mj"],str);
                        if (check < 3) return "";
                        else return P4Data["Id"];
                }
                return "";
        }
        if (kind=="peng")
        {
                check=do_check_Mj(P1Data["AutoPeng"],str);
                if (check!=0)
                {
                        check=do_check_Mj(P1Data["Mj"],str);
                        if (check < 2) return "";
                        else return P1Data["Id"];
                }
                check=do_check_Mj(P2Data["AutoPeng"],str);
                if (check!=0)
                {
                        check=do_check_Mj(P2Data["Mj"],str);
                        if (check < 2) return "";
                        else return P2Data["Id"];
                }
                check=do_check_Mj(P3Data["AutoPeng"],str);
                if (check!=0)
                {
                        check=do_check_Mj(P3Data["Mj"],str);
                        if (check < 2) return "";
                        else return P3Data["Id"];
                }
                check=do_check_Mj(P4Data["AutoPeng"],str);
                if (check!=0)
                {
                        check=do_check_Mj(P4Data["Mj"],str);
                        if (check < 2) return "";
                        else return P4Data["Id"];
                }
                return "";
        }
        if (kind=="player")
        {
                for (i=0;i<Play;i++)
                {
                        if (NowPlayerId[i]==str) check=1;
                }
                if (check) return "Y";
                return "";
        }
}

int delete_last_dump(string whoId)
{
        mapping who;
        if (LastDumpId==P1Data["Id"]) who=P1Data;
        else if (LastDumpId==P2Data["Id"]) who=P2Data;
        else if (LastDumpId==P3Data["Id"]) who=P3Data;
        else if (LastDumpId==P4Data["Id"]) who=P4Data;
        if (who["Dump"]!="") who["Dump"]=do_delete_Mj(who["Dump"],LastDump,1);
        return 1;
}

//把英文字转为代码 or 中文 flag 1 就是转为代码 flag 2 转为1..9
mixed do_check_num(string str,int flag)
{
        int number;

        if (!str) return MjC[0];
        sscanf(str,"%d%s",number,str);
        if (number == 0)
        {
                if (str=="ea") number=28;
                else if (str=="so") number=29;
                else if (str=="we") number=30;
                else if (str=="no") number=31;
                else if (str=="jo") number=32;
                else if (str=="fa") number=33;
                else if (str=="ba") number=34;
                else if (str=="f1") number=35;
                else if (str=="f2") number=36;
                else if (str=="f3") number=37;
                else if (str=="f4") number=38;
                else if (str=="f5") number=39;
                else if (str=="f6") number=40;
                else if (str=="f7") number=41;
                else if (str=="f8") number=42;
                else if (str=="xx") number=43;
        } else
        {
                if (str=="w") number=0+number;
                else if (str=="t") number=9+number;
                else if (str=="s") number=18+number;
                if (flag==2)
                {
                        number%=9;
                        if (number==0) number=9;
                }
        }
        if (!flag) return MjC[number];
        else return number;
}

void check_flower(mapping who)
{
        string newstr = "",str=who["Mj"],temp,temp1;
        int i = strlen(str),j;

        while(i--)
        {
                i--;
                temp=str[i..i+1];
                if (temp=="f1"||temp=="f2"||temp=="f3"||temp=="f4"|| temp=="f5"||temp=="f6"||temp=="f7"||temp=="f8")
                {
                        if (Playing)
                        {
                                tell_room(environment(this_object()),this_player()->name()+"说道："+HIB+"花牌"+NOR+"补花。\n\n"+this_player()->name()+"往后面补了一张牌。\n",this_player());
                                tell_object(this_player(),"你说道："+HIB+"花牌"+NOR+"补花。\n\n你往后面补了一张牌。\n");
                                tell_object(this_player(),"你摸到了一张"+do_check_num(List[end..end+1],0)+"。\n");
                        }
                        HU_F=1;
                        who["OutFlower"]+=temp;
                        str[i..i+1]=List[end..end+1];
                        end-=2;
                        i+=2;
                        continue;
                }
                else newstr+=temp;
        }
        who["Mj"]=sort_data(newstr);
}

int do_check_Mj(string datastr,string str)
{
        int size=strlen(datastr),check=0;

        while(size--)
        {
                size--;
                if (datastr[size..size+1]==str) check++;
        }
        return check;
}

string do_delete_Mj(string datastr,string str,int amount)//把某牌去掉
{
        int size=strlen(datastr),check;
        string temp="";

        while(size--)
        {
                size--;
                if (datastr[size..size+1]==str && amount!=0) amount--;
                else temp+=datastr[size..size+1];
        }
        size=strlen(temp);
        datastr=temp;
        temp="";
        while(size--)
        {
                size--;
                temp+=datastr[size..size+1];
        }
        return temp;
}

string sort_data(string str)
{
        int i = strlen(str),a,b,c,d;

        string newstr="",temp="";
        for (a=-1;a<i;a++)
        {
                a++;
                for (b=a+2;b<i;b++)
                {
                        b++;
                        c=do_check_num(str[a..a+1],1);
                        d=do_check_num(str[b-1..b],1);
                        if (c < d)
                        {
                                temp=str[a..a+1];
                                str[a..a+1]=str[b-1..b];
                                str[b-1..b]=temp;
                        }
                }
        }
        return str;
}

int do_look(string arg)
{
        int i,l;
        object me=this_player();
        string Mj="",p1o="",p2o="",p3o="",p4o="";
        mapping who;

        if (query_verb()==".") arg="mj";
        if (query_verb()=="..") arg="chicken";
        if (query_verb()==".1") arg="1p";
        if (query_verb()==".2") arg="2p";
        if (query_verb()==".3") arg="3p";
        if (query_verb()==".4") arg="4p";
        if (query_verb()==".0") arg="all";
        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        else return 0;
        if (who["Auto"]=="auto") l=1;
        if (arg=="1p"||arg=="2p"||arg=="3p"||arg=="4p"||arg=="all"||arg=="chicken"||arg=="end"||arg=="da"||arg=="mj");
        else return 0;
        if (arg=="1p") who=P1Data;
        if (arg=="2p") who=P2Data;
        if (arg=="3p") who=P3Data;
        if (arg=="4p") who=P4Data;
        if (arg=="1p"||arg=="2p"||arg=="3p"||arg=="4p")
        {
                i=0;
                if (who["Show"]=="代码") i=3;
                if (who["Show"]=="color") i=5;
                if( !Playing || check_id(query("id", me),"player") == "" || l == 1 )
                {
                        if (who["OutGang"]!="")
                        {
                                Mj+=who["Id"]+":暗杠的牌有\n";
                                Mj+=show_mj(who["OutGang"],i+1);
                        }
                        Mj+=who["Id"]+":手中的牌有\n";
                        Mj+=show_mj(who["Mj"],i);
                }
                Mj+=who["Id"]+":摆在外面的牌有\n";
                Mj+=show_mj(who["Out"]+who["OutPeng"]+who["OutFlower"],i+1);
                Mj+=who["Id"]+":打过的牌:\n";
                Mj+=show_mj(who["Dump"],2);
        }
        else if (arg=="mj")
                {
                        if (!Playing) return 0;
                        if (who["OutGang"]!="")
                        {
                                Mj+="你的暗杠的牌有\n";
                                Mj+=show_mj(who["OutGang"],1);
                        }
                        if (who["Show"]=="代码") i=3;
                        if (who["Show"]=="color") i=5;
                        Mj+="你摆在外面的牌有\n";
                        Mj+=show_mj(who["Out"]+who["OutPeng"]+who["OutFlower"],i+1);
                        Mj+="你手中的牌有\n";
                        Mj+=show_mj(who["Mj"],i);
                        Mj+="你的设定有";
                } else if (arg=="all")
                        {
                                i=0;
                                if (who["Show"]=="代码") i=3;
                                if (who["Show"]=="color") i=5;
                                Mj+=P1Data["Id"]+":摆在外面的牌有\n";
                                Mj+=show_mj(P1Data["Out"]+P1Data["OutPeng"]+P1Data["OutFlower"],i+1);
                                Mj+=P1Data["Id"]+":打过的牌有\n";
                                Mj+=show_mj(P1Data["Dump"],2)+"\n";
                                Mj+=P2Data["Id"]+":摆在外面的牌有\n";
                                Mj+=show_mj(P2Data["Out"]+P2Data["OutPeng"]+P2Data["OutFlower"],i+1);
                                Mj+=P2Data["Id"]+":打过的牌有\n";
                                Mj+=show_mj(P2Data["Dump"],2)+"\n";
                                Mj+=P3Data["Id"]+":摆在外面的牌有\n";
                                Mj+=show_mj(P3Data["Out"]+P3Data["OutPeng"]+P3Data["OutFlower"],i+1);
                                Mj+=P3Data["Id"]+":打过的牌有\n";
                                Mj+=show_mj(P3Data["Dump"],2)+"\n";
                                Mj+=P4Data["Id"]+":摆在外面的牌有\n";
                                Mj+=show_mj(P4Data["Out"]+P4Data["OutPeng"]+P4Data["OutFlower"],i+1);
                                Mj+=P4Data["Id"]+":打过的牌有\n";
                                Mj+=show_mj(P4Data["Dump"],2)+"\n";
                        } else if (arg=="chicken")
                                {
                                        if (Playing)
                                        {
                                                Mj=LookP+"俩眼眯成一条缝儿，正聚精会神地打牌呢。\n";
                                                Mj+="还剩下"+sprintf("%d",(end-count-16-Goned)/2)+"张牌就流局了。\n";
                                                if (LastDump!="")
                                                        Mj+=LastDumpId+"刚刚打出了"+show_mj(LastDump,2)+"。\n";
                                                if (Count)
                                                        Mj+=NowPlayerId[0]+":连庄"+chinese_number(Count)+"。\n";
                                                if (P1Data["Out"]=="" && P1Data["OutPeng"]=="")
                                                        p1o=HIY+"门清"+NOR;
                                                if (P2Data["Out"]=="" && P2Data["OutPeng"]=="")
                                                        p2o=HIY+"门清"+NOR;
                                                if (P3Data["Out"]=="" && P3Data["OutPeng"]=="")
                                                        p3o=HIY+"门清"+NOR;
                                                if (P4Data["Out"]=="" && P4Data["OutPeng"]=="")
                                                        p4o=HIY+"门清"+NOR;
                                                Mj+="1.东家是:"+NowPlayerId[0]+p1o+"\n2.南家是:"+NowPlayerId[1]+p2o+"\n";
                                                Mj+="3.西家是:"+NowPlayerId[2]+p3o+"\n4.北家是:"+NowPlayerId[3]+p4o+"\n";
                                        }
                                        else if (NowPlayerId[0]!="") Mj=LookP+"正在等人打牌。";
                                        else Mj=LookP+"一只麻将鸡正等人加入(sit)牌局。";
                                } else if (arg=="end")
                                        {
                                                Mj+="还有"+chinese_number((end-count-16-Goned)/2)+"张牌就流局了。\n";
                                        } else if (arg=="da")
                                                {
                                                        Mj+=LastDumpId+"刚刚打出了"+show_mj(LastDump,2)+"。\n";
                                                } else return 0;
        if (arg=="mj")
        {
                if (who["AutoTin"]!="")
                        Mj+="遇到"+show_mj(who["AutoTin"],2)+"会自动胡牌、";
                if (who["AutoGang"]!="")
                        Mj+="遇到"+show_mj(who["AutoGang"],2)+"会自动杠牌、";
                if (who["AutoPeng"]!="")
                        Mj+="遇到"+show_mj(who["AutoPeng"],2)+"会自动碰牌。";
                if (who["Show"]=="代码") Mj+="显示方式为代码方式。";
                if (who["Show"]=="color") Mj+="显示方式为彩色。";
                if (who["Auto"]=="auto") Mj+="你设定自动听牌。";
                if (who["AutoTin"]==""&&who["AutoGang"]==""&&who["AutoPeng"]==""&&who["Show"]==""&&who["Auto"]=="")
                        Mj+="你没有任何设定。\n";
        }
        printf("%s\n",Mj);
        return 1;
}

int do_help(string str)
{
        if (str=="setmj")
        {
write(@HELP

                       基  本  设  定

            setmj 可用的有自动胡、杠 、碰、听、显式方法。
--------------------------------------------------------------------
例子1: setmj peng 1w    设定会自动碰1w 当别人打出一万时会自动碰一万。
       setmj gang 1w    设定会自动杠1w 当别人打出一万时会自动杠一万。
       setmj ting 1w    设定会自动听1w 当别人打出一万时会自动胡一万。
例子2: setmj show 代码  设定为只显示代码。
       setmj show color 设定为彩色显示。
例子3: setmj ting none  取消会自动胡牌设定。
       setmj gang none  取消会自动杠牌设定。
       setmj peng none  取消会自动碰牌设定。
例子4: setmj auto ting  设定自动听牌。
--------------------------------------------------------------------
HELP);
                return 1;
        }
        return 0;
}

int to_say_play()
{
        write(@HELP

  指  令        例          子              说    明
┌--------------------------------------------------------------------------------------┐
│sit ----------------------------------------------------------- 坐下入局 │
│look  l mj或.看自己牌,l 1p或.1看玩家1的牌           │
│      l all或..看全部,l end看流局l dump。  看牌     │
│mo  ----------------------------------------------------------- 摸牌     │
│da            da <代码>。                  打牌     │
│chi           chi <代码1> <代码2>。        吃牌     │
│peng----------------------------------------------------------- 碰牌     │
│gang          gang 或 gang <代码>(暗杠用)  杠牌     │
│hu  ----------------------------------------------------------- 胡牌     │
│setmj         请看桌面(look table)         设定参数 │
│star----------------------------------------------------------- 牌局开始 │
│restart       restart 或 restart mj        重新开始 │
│top   top aip,top -p,top -w,top -h,top -d           │
│      top -l看全部,-lw,-lh,-ld。           查资料   │
└--------------------------------------------------------------------------------------┘

HELP);
                  return 1;
}

int to_say_rule()
{
write(@HELP

　　每胡就有底台５，在加上所得的台就是总台，要是自摸就＊３，相
当於五一的算法。放枪就由总战绩那扣掉所失的台数。胡者则加上去。

HELP);
                  return 1;
}

int show_top(string str)
{
        int i,check,a,b,c,d,e;
        string *temp=({"","","","","",""});
        string show="";
        mixed *MjData;

        if( !str)str=query("id", this_player());
        else if (str=="-lp"||str=="-pl"||str=="-l") str="all1";
        else if (str=="-lw"||str=="-wl") str="all2";
        else if (str=="-lh"||str=="-hl") str="all3";
        else if (str=="-ld"||str=="-dl") str="all4";
        if (file_size(MJ_DATA)==-1)
                return notify_fail("资料档没没有找到。\n");
        MjData=explode(read_file(MJ_DATA),",");
        if (str=="all1") e=2;
        else if (str=="all2") e=3;
        else if (str=="all3") e=4;
        else if (str=="all4") e=5;
        if (str=="all1"||str=="all2"||str=="all3"||str=="all4") str="all";
        if (str=="-p") e=2;
        else if (str=="-w") e=3;
        else if (str=="-h") e=4;
        else if (str=="-d") e=5;
        if (str=="all"||str=="-p"||str=="-w"||str=="-h"||str=="-d")
        {
                for (a=0;a<sizeof(MjData);a+=6)
                {
                        for (b=a+6;b<sizeof(MjData);b+=6)
                        {
                                sscanf(MjData[a+e],"%d",c);
                                sscanf(MjData[b+e],"%d",d);
                                if (d > c)
                                {
                                        for (i=0;i<6;i++)temp[i]=MjData[a+i];
                                        for (i=0;i<6;i++) MjData[a+i]=MjData[b+i];
                                        for (i=0;i<6;i++) MjData[b+i]=temp[i];
                                }
                        }
                }
        }
        show=HBWHT+"\n  ";
        for (i=0; i<34; i++) show+="[47m　";
        show+=HBWHT+"  \n";
        show+="  "+HBRED+"   英文名字 │  中文名字  │已玩局数│ 总战绩 │自摸次数│放枪次数  "+HBWHT+"  \n";
        if (str=="all")
        {
                for (i=0; i<sizeof(MjData); i+=6)
                {///
                        show+="  "+HBRED;
                        show+=sprintf("  %10s│%12s│%8s│%8s│%8s│%8s  ", MjData[i],MjData[i+1],MjData[i+2],MjData[i+3],MjData[i+4],MjData[i+5]);
                        show+=HBWHT+"  \n";
                }
        } else if (str=="-p"||str=="-w"||str=="-h"||str=="-d")
                {
                        if (sizeof(MjData) < 60) d=sizeof(MjData);
                        else d=60;
                        for (i=0; i<d; i+=6)
                        {///
                                show+="  "+HBRED;
                                show+=sprintf("  %10s│%12s│%8s│%8s│%8s│%8s  ", MjData[i],MjData[i+1],MjData[i+2],MjData[i+3],MjData[i+4],MjData[i+5]);
                                show+=HBWHT+"  \n";
                        }
                } else
                {
                        for (i=0; i<sizeof(MjData); i+=6)
                        {
                                if (MjData[i]==str)
                                {
                                        check=1;
                                        break;
                                }
                        }
                        if (check==1)
                        {
                                show+="  "+HBRED;
                                show+=sprintf("  %10s│%12s│%8s│%8s│%8s│%8s  ", MjData[i],MjData[i+1],MjData[i+2],MjData[i+3],MjData[i+4],MjData[i+5]);
                                show+=HBWHT+"  \n";
                        } else return notify_fail("没有这个人的资料。\n");
                }
        show+=HBWHT+"  ";
        for (i=0; i<34; i++) show+="[47m　";
        show+=HBWHT+"  "+NOR+"\n";
        printf("%s\n",show);
        return 1;
}

int set_mjdata(object me,int *winner)
{
        int i,check;
        string str="";
        mixed *MjData;

        if (!me||!winner) return 0;
        if (file_size(MJ_DATA)==-1);
        else
        {
                MjData=explode(read_file(MJ_DATA),",");
                for (i=0; i<sizeof(MjData); i+=6)
                {
                        if( MjData[i] == query("id", me) )
                        {
                                check=1;
                                break;
                        }
                }
        }
        if (check==1)
        {
                MjData[i+2]=sprintf("%d",winner[0]);
                MjData[i+3]=sprintf("%d",winner[1]);
                MjData[i+4]=sprintf("%d",winner[2]);
                MjData[i+5]=sprintf("%d",winner[3]);
                for (i=0; i<sizeof(MjData); i++) str+=MjData[i]+",";
                write_file(MJ_DATA,str,1);
        } else
        {
                str=query("id", me)+",";
                str+=me->name()+",";
                str+=winner[0]+",";
                str+=winner[1]+",";
                str+=winner[2]+",";
                str+=winner[3]+",";
                write_file(MJ_DATA,str,0);
        }
        return 1;
}

int *get_mjdata(string Id)
{
        int i,check,*winner=({0,0,0,0});
        string str="";
        mixed *MjData;

        if (!Id) return 0;
        if (file_size(MJ_DATA)==-1) return 0;
        MjData=explode(read_file(MJ_DATA),",");
        for (i=0; i<sizeof(MjData); i+=6)
        {
                if (MjData[i]==Id)
                {
                        check=1;
                        break;
                }
        }
        if (check==1)
        {
                sscanf(MjData[i+2],"%d",winner[0]);
                sscanf(MjData[i+3],"%d",winner[1]);
                sscanf(MjData[i+4],"%d",winner[2]);
                sscanf(MjData[i+5],"%d",winner[3]);
        }
        return winner;
}

int get_tc(mapping who)
{
        int size,i,check;
        string str,tempW="",tempT="",tempS="",tempB="";
        str=who["Mj"]+who["Out"]+who["OutPeng"]+who["OutGang"];
        //庄家
        if (NowPlayerId[0]==who["Id"]) Tc+="@1";
        //门清&自摸
        if (who["Out"]==""&&who["OutPeng"]==""&&Touched) Tc+="@l";
        else if (who["Out"]==""&&who["OutPeng"]=="") Tc+="@4";
        else if (Touched) Tc+="@2";
        //全求人
        if (strlen(who["Mj"]) < 5) Tc+="@i";
        size=strlen(str);
        while(size--)
        {
                size--;
                if (do_check_num(str[size..size+1],1) < 10)
                        tempW+=str[size..size+1];
                else if (do_check_num(str[size..size+1],1) < 19)
                                tempT+=str[size..size+1];
                        else if (do_check_num(str[size..size+1],1) < 28)
                                        tempS+=str[size..size+1];
                         else tempB+=str[size..size+1];
        }
        //风牌
        if (Times/Play==0 && NowPlayerId[0]==who["Id"] && do_check_Mj(tempB,"ea")>2)
                Tc+="@e";
        else if (Times/Play==0 && do_check_Mj(tempB,"ea") > 2 || NowPlayerId[0]==who["Id"] && do_check_Mj(tempB,"ea")>2)
                        Tc+="@5";

        if (Times/Play==1 && NowPlayerId[1]==who["Id"] && do_check_Mj(tempB,"so")>2)
                Tc+="@f";
        else if (Times/Play==1 && do_check_Mj(tempB,"so") > 2 || NowPlayerId[1]==who["Id"] && do_check_Mj(tempB,"so")>2)
                        Tc+="@6";

        if (Times/Play==2 && NowPlayerId[2]==who["Id"] && do_check_Mj(tempB,"we")>2)
                Tc+="@g";
        else if (Times/Play==2 && do_check_Mj(tempB,"we") > 2 || NowPlayerId[2]==who["Id"] && do_check_Mj(tempB,"we")>2)
                        Tc+="@7";

        if (Times/Play==3 && NowPlayerId[3]==who["Id"] && do_check_Mj(tempB,"no")>2)
                Tc+="@h";
                  else if (Times/Play==3 && do_check_Mj(tempB,"no") > 2 || NowPlayerId[3]==who["Id"] && do_check_Mj(tempB,"no")>2)
                        Tc+="@8";
        //花牌
        if (sizeof(who["OutFlower"])==16)
                Tc+="@A";
        //八仙过海
        else if (sizeof(who["OutFlower"])==14 && sizeof(P1Data["OutFlower"]+P2Data["OutFlower"]+P3Data["OutFlower"]+P4Data["OutFlower"])==16)
                        Tc+="@D";
        //七抢一
                else if (do_check_Mj(who["OutFlower"],"f1")==1 && do_check_Mj(who["OutFlower"],"f2")==1 && do_check_Mj(who["OutFlower"],"f3")==1 && do_check_Mj(who["OutFlower"],"f4")==1)
                                Tc+="@B";
        //春夏秋冬
                        else if (do_check_Mj(who["OutFlower"],"f5")==1 && do_check_Mj(who["OutFlower"],"f6")==1 && do_check_Mj(who["OutFlower"],"f7")==1 && do_check_Mj(who["OutFlower"],"f8")==1)
                                        Tc+="@C";
        //梅兰菊竹
                                else if (NowPlayerId[0]==who["Id"] && do_check_Mj(who["OutFlower"],"f1")==1 || NowPlayerId[0]==who["Id"]&&do_check_Mj(who["OutFlower"],"f5")==1 || NowPlayerId[1]==who["Id"]&&do_check_Mj(who["OutFlower"],"f2")==1 || NowPlayerId[1]==who["Id"]&&do_check_Mj(who["OutFlower"],"f6")==1 || NowPlayerId[2]==who["Id"]&&do_check_Mj(who["OutFlower"],"f3")==1 || NowPlayerId[2]==who["Id"]&&do_check_Mj(who["OutFlower"],"f7")==1 || NowPlayerId[3]==who["Id"]&&do_check_Mj(who["OutFlower"],"f4")==1 || NowPlayerId[3]==who["Id"]&&do_check_Mj(who["OutFlower"],"f8")==1)
                                                Tc+="@3";
        //清一色跟字一色
        if (tempW!=""&&tempT==""&&tempS==""&&tempB=="") Tc+="@q";
        else if (tempW==""&&tempT!=""&&tempS==""&&tempB=="") Tc+="@q";
        else if (tempW==""&&tempT==""&&tempS!=""&&tempB=="") Tc+="@q";
        else if (tempW==""&&tempT==""&&tempS==""&&tempB!="") Tc+="@r";
        //混一色
        if (tempW!=""&&tempT==""&&tempS==""&&tempB!="")
                Tc+="@n";
        else if (tempW==""&&tempT!=""&&tempS==""&&tempB!="")
                        Tc+="@n";
        //绿一色
                else if (tempW==""&&tempT==""&&tempS!=""&&tempB!="")
                        {
                                if (do_check_Mj(tempB,"fa")==3&&sizeof(tempB)==6
                                ||  do_check_Mj(tempB,"fa")==2&&sizeof(tempB)==4
                                && do_check_Mj(tempS,"1s")==0&& do_check_Mj(tempS,"5s")==0
                                && do_check_Mj(tempS,"7s")==0&& do_check_Mj(tempS,"9s")==0)
                                        Tc+="@E";
                                else Tc+="@n";
                        }
        //大三元
        if (do_check_Mj(tempB,"jo") > 2
        &&  do_check_Mj(tempB,"fa") > 2
        &&  do_check_Mj(tempB,"ba") > 2) Tc+="@t";
        //小三元
        else if (do_check_Mj(tempB,"jo") > 1
                &&  do_check_Mj(tempB,"fa") > 1
                &&  do_check_Mj(tempB,"ba") > 1) Tc+="@o";
                else if (do_check_Mj(tempB,"jo") > 2) Tc+="@9";
                        else if (do_check_Mj(tempB,"fa") > 2) Tc+="@0";
                                else if (do_check_Mj(tempB,"ba") > 2) Tc+="@a";
        //大四喜
        if (do_check_Mj(tempB,"ea") > 2
                &&  do_check_Mj(tempB,"so") > 2
                &&  do_check_Mj(tempB,"we") > 2
                &&  do_check_Mj(tempB,"no") > 2) Tc+="@v";
        //小四喜
        else if (do_check_Mj(tempB,"ea") > 1
                        &&  do_check_Mj(tempB,"so") > 1
                        &&  do_check_Mj(tempB,"we") > 1
                        &&  do_check_Mj(tempB,"no") > 1) Tc+="@F";

        for (i=0;i<sizeof(str);i+=2)
        {
                if (str[i..i+1]=="xx") continue;
                if (do_check_Mj(str,str[i..i+1])==3) check++;
                else if (do_check_Mj(str,str[i..i+1])==4) check++;
        }
        //碰碰胡
        if (check>14)
        {
                if (who["Out"]==""&&who["OutPeng"]==""&&do_check_Mj(Tc,"@u")==0)
                        Tc+="@m@u";
                else  Tc+="@m";
        }
        check=0;
        for (i=0;i<sizeof(str);i+=2)
        {
                if (do_check_num(str[i..i+1],1)!=1&&do_check_num(str[i..i+1],1)>8)
                        check++;
        }
        if (check=0&&tempB!="") Tc+="@I";//混老头
        else if (check=0&&tempB="") Tc+="@J";//清老头
        //平胡
        if (tempB==""&&who["OutFlower"]==""&&check==0&&sizeof(who["AutoTin"])>3)
                Tc+="@d";
        //河底摸月
        if (count==((end-16-(Goned*2))-2)&&Touched) Tc+="@b";
        //捞鱼
        if (count==((end-16-(Goned*2))-2)&&!Touched) Tc+="@c";
        //天胡
        if (LastDump==""&&count==(Play*2*16)+2) Tc+="@w";
        //地胡&人胡
        printf("%d > %d\n",count,((Play*2*16)+(Play*2)));
        if (count < ((Play*2*16)+(Play*2))
                &&P1Data["Out"]==""&&P1Data["PengOut"]==""
                &&P2Data["Out"]==""&&P2Data["PengOut"]==""
                &&P3Data["Out"]==""&&P3Data["PengOut"]==""
                &&P4Data["Out"]==""&&P4Data["PengOut"]=="")
        {
                if (Touched) Tc+="@x";
                else Tc+="@y";
        }
        return 1;
}
int ch(string str)
{
        object me=this_player();
        mapping who;
        if( query("id", me) == P1Data["Id"])who=P1Data;
        else if( query("id", me) == P2Data["Id"])who=P2Data;
        else if( query("id", me) == P3Data["Id"])who=P3Data;
        else if( query("id", me) == P4Data["Id"])who=P4Data;
        if (!str) return 0;
        write("你把牌"+who["Mj"]+"换成"+str+" ok.\n");
        str=sort_data(str);
        who["Mj"]=str;
        return 1;
}
