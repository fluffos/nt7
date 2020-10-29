#include <ansi.h>
inherit NPC;
#include "/quest/quest4/chousha.h"
#include "/quest/quest4/place_room.h"
//#include "zuji.h"

string ask_shengsi();
string ask_zuji();
void load_killer(int num);
int killer_times;
void create()
{
        set_name("无名老人", ({ "wuming laoren", "wuming", "laoren"}));
        set("gender", "男性");
        set("age", 120);
        //set("nickname", HIW"古往今来 " HIM" 无所不知 "HIG" 笑傲江湖 "HIY" 天下无敌" NOR);
        set("nickname", HIY "王者归来" NOR);
        set("title", HIG "笑傲江湖" NOR); 
        set("long",
                "传说中的武林前辈，据说此老乃百年前的武林宿耄，现今已百岁高龄。\n"
                "他笑傲武林数十载，天下的武功，各门各派奇闻轶事，古往今来武林\n"
                "典故，号称是“无所不知，无所不晓”。一身武功是出神入化，罕逢\n"
                "敌手，至今数十年未曾与人动手。多年来一直隐居扬州城中评书为生，\n"
                "每日在此讲述武林典故。\n");

        set("combat_exp", 15000000);
        set("shen_type", 1);
        set("max_neili", 40000);
        set("neili", 40000);
        set("max_qi",10000);
        set("max_jing",5000);
        set("max_jingli",10000);
        set("jingli",10000);
        set("per",25);
        set("jiali", 400);

        set_skill("force", 650);
        set_skill("quanzhen-jianzhen", 800);
        set_skill("array", 800);
        set_skill("quanzhen-xinfa", 700);
        // set_skill("xuanmen-neigong", 380);
        set_skill("unarmed", 700);
        set_skill("xiantian-gong", 650);
        set_skill("dodge", 700);
        // set_skill("tianshan-feidu", 360);
        set_skill("jinyan-gong", 700);
        set_skill("parry", 700);
        set_skill("jinguan-yusuo", 700);
        set_skill("strike", 700);
        set_skill("chongyang-shenzhang", 660);
        set_skill("haotian-zhang", 700);
        set_skill("finger", 700);
        set_skill("zhongnan-zhi", 660);
        set_skill("sun-finger", 700);
        // set_skill("qixing-shou", 380);
        set_skill("sword", 700);
        // set_skill("qixing-jian", 360);
        // set_skill("tonggui-jian", 360);
        set_skill("quanzhen-jian", 700);
        // set_skill("tiangang-chenfa", 340);
        set_skill("taoism", 650);
        set_skill("literate", 650);
        set_skill("huajia-su", 700);
        set_skill("martial-cognize", 650);
        set_skill("medical", 680);
        set_skill("liandan-shu", 680);
        set_skill("cuff",680);
        set_skill("whip",680);
        set_skill("chunyang-quan",680);
        set_skill("duanyun-bian",680);
        set_skill("array",650);
        set_skill("beidou-zhenfa", 650);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        // map_skill("whip", "tiangang-chenfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "haotian-zhang");
        map_skill("unarmed", "xiantian-gong");
        map_skill("finger", "sun-finger");
        map_skill("strike", "haotian-zhang");
        // map_skill("hand", "qixing-shou");
        map_skill("cuff",   "chunyang-quan");
        map_skill("whip",   "duanyun-bian");
        prepare_skill("unarmed", "xiantian-gong");



        set("inquiry", ([
                "生死状": (: ask_shengsi:),
                "生死"  : (: ask_shengsi :),
                //"阻击"  : (: ask_zuji:),
        ]) );

        set("chat_chance", 10);
        set("chat_msg", ({  
                CYN"无名老人捋了捋长须，哈哈大笑道：“张三丰那小道士，现在算起来也该有些出息了！”\n"NOR,
                CYN"无名老人轻抚掌中剑匣，无不得意地说道：“老夫纵横江湖百余载，还真没遇到过对手！”\n"NOR,
                CYN"无名老人微显扭捏之色，叹道：“林朝英那丫头，现在也不知道怎么样了。” \n"NOR, 
        }));  

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.hun" :),
                (: perform_action, "unarmed.fen" :),
                (: perform_action, "unarmed.dang" :),
                (: perform_action, "unarmed.jian" :),
                (: perform_action, "parry.suo" :),
                (: exert_function, "hup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("family/family_name","全真教");
        setup();

        carry_object("/d/city/npc/obj/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        
}

void init()
{
        object ob = this_object();
        
/*
        if( interactive (ob) )
        {
                remove_call_out("story_check");
                remove_call_out("check_time");
        }

        if( !query_temp("story_start", ob) )
        {
                call_out("story_check",2);
                set_temp("story_start", 1, ob);
        }          
        
        if( !query_temp("check_time", ob) )
        {
                call_out("check_time", 1);
                set_temp("check_time", 1, ob);
        }
*/
}


int check_time()
{
        object *ulist;
        int num,n,chousha_count;
        object me=this_object();
        string temp;

        ulist=users();
        num=sizeof(ulist);
        num=num/2+random(num/2);
        if( num > 30 ) num=30;

        if( (time()-query("chousha_begin")) > 5400 && num>9 && !query("chousha") )
        {
                temp=read_file("/quest/quest4/chousha_count",1,1);
                chousha_count=atoi(temp);
                //if( chousha_count >= 5 && zuji_times < 1 )
/*
                if( 0 )
                {
                        set("chousha_begin",time()); 
                        temp=sprintf("%d",time());
                        write_file("/quest/quest4/time_begin",temp,1);   

                        zuji_times=1;

                         message("channel:rumor", 
                                MAG"【故事传闻】少林方丈玄慈接到一封信件。\n" 
                                "信中写道：契丹国有大批武士要来偷袭少林寺，想将寺中秘藏数百年的武功图谱一举夺去。\n"
                                "玄慈大师心想：不行，要是契丹此举成功，大宋便有亡国之祸。\n"
                                "玄慈大师一看，信中还写道：听说这些契丹武士要道经雁门。\n"
                                "玄慈大师心想：要在雁门关外迎击，纵不能尽数将之歼灭，也要令他们的奸谋难以得逞。\n"
                                "玄慈大师盘算：丐帮汪帮主，万胜刀王维义，黄山鹤云道长，还有一些武林朋友都可以去迎击。\n"
                                "玄慈大师盘算：但是恐怕敌人人数还是会比我们多得多，况且我们这边武功精强者也是寥寥无几。\n"
                                "玄慈大师发愁：这可怎么办呢？\n"
                                "玄慈大师深深地叹了口气。\n"
                                ".........\n"
                                NOR+BLINK+HIW"一场血战即将在雁门关外展开.........\n"NOR,users());
                        call_out("zuji_begin",180,num);  
                        call_out("zuji_close",3600);
                        call_out("remove_enemy",3600);
                } else 
*/
                {
                        chousha_count++;
                        temp=sprintf("%d",chousha_count);
                        write_file("/quest/quest4/chousha_count",temp,1);

                        message("channel:rumor",
                                MAG"【江湖】"NOR+
                                HIB"据说江湖中某两大门派为解宿怨，一个时辰内要以武力解决。\n"NOR,users());
                                set("chousha_begin",time());
                                set("chousha",1);
                                temp=sprintf("%d",time());
                                write_file("/quest/quest4/time_begin",temp,1);
                        call_out("chousha_begin",60);
                }
        }

        if((time()-query("chousha_begin")) > 10 && query("chousha")
           && (time()-query("chousha_begin")) < 60)    
        message("channel:rumor", MAG"【江湖】"NOR+
        HIB"据可靠消息，会有两大门派在不久以后大火拼。\n"NOR,users());
        if((time()-query("chousha_begin")) > 70 && query("chousha") 
           && query("chousha")<4)
        {
         addn("chousha",1);
         message("channel:rumor", MAG"【江湖】"NOR+HIR+fam1
         +HIC"与"+HIR+fam2
         +HIC"两大门派积怨已久，此刻正在北京城正相互仇杀。\n"NOR,users());
        }

        if( query("chousha") == 4 )
        {
             addn("chousha",1);
             load_killer(num);
        }

        remove_call_out("check_time");
        call_out("check_time",30);
        return 1;
}



void load_killer(int num)
{
         object killer1,killer2;
         int n,time,exp_rate;
         string temp;

         if( killer_times >= 4 )
         {
                killer_times=1;
                remove_call_out("load_killer");
                exp_rate=6;
                temp=sprintf("%d",exp_rate);
                write_file("/quest/quest4/exp_rate",temp,1); 
                return;
         }

         killer_times++;
         for(n=0;n<num;n++)
         {
                time=query("chousha_begin")+1800-time();
                killer1=new("/quest/quest4/killer1");
                place_room("西城",killer1);
                killer2=new("/quest/quest4/killer2");
                place_room("东城",killer2);
                killer1->start_escape(time);    
                killer2->start_escape(time);
        } 

         remove_call_out("load_killer");
         call_out("load_killer",10,num);
         return;
}

int story_check()
{
        string *story_msg=({}),str;
        int story_msg_len;

        story_msg+= ( {"宝刀屠龙，号令武林，倚天不出，谁与争锋！\n"} );
        story_msg+= ( {"少林禅宗精不老，武当道学气绵绵。\n"} );
        story_msg+= ( {"古墓创派方三代，幽居古墓潜修心。\n"
"                      银索金铃玄铁剑，玉石俱焚鬼神伤。\n"} );
        story_msg+= ( {"华山自古称剑宗，独孤九剑傲四方。"} );
        story_msg+= ( {"桃花岛主鬼谷才，奇门五行遁无影。\n"
"                      碧海潮生歌一曲，方圆百里人心慌。\n"} );
        story_msg+= ( {"日月教下尽阉党，葵花辟邪势莫挡。"} );
        story_msg+= ( {"先天功驭全真剑，重阳一生不输人。"} );
        story_msg+= ( {"明教绝艺圣火令，七伤挪移妙无双。"} );
        story_msg+= ( {"丐帮四海皆为家，露宿偷讨不亦忙。\n"
"                      刚猛无敌降龙掌，精妙轻灵打狗棒。\n"} );
        story_msg+= ( {"慕容家传尽绝艺，斗转星移众莫敌。\n"
"                      剑指飞扬尽随意，光复大燕待后人。"} );
        story_msg+= ( {"星宿门下善使毒，毒掌化功魂魄寒。\n"} );
        story_msg+= ( {"峨嵋不问世俗事，静坐参悟大乘功。\n"
"                      渡世济人自修身，妙用无穷临济庄。\n"} );           
        story_msg+= ( {"少林自古多绝艺，惊魔一指不寻常。\n"
"                      习尽醉棍达摩剑，三渡座下日月鞭。\n"} );
        story_msg+=( {"赵客缦胡缨，吴钩霜雪明。\n"
"                      银鞍照白马，飒沓如流星；\n"
"                      十步杀一人，千里不留行；\n"
"                      事了拂衣去，深藏身与名；\n"
"                      闲过信陵饮，脱剑膝前横；\n"
"                      将炙啖朱亥，持觞劝侯嬴；\n"
"                      三杯吐然诺，五狱倒为轻；\n"
"                      眼花耳热后，竞气素霓生；\n"
"                      救赵挥金锤，邯郸先震惊；\n"
"                      千秋二壮士，亘赫大梁城；\n"
"                      纵死侠骨香，不惭世上英；\n"
"                      谁能书阁下，白首太玄经。\n" });
        story_msg+= ( {"段家绝艺非寻常，六脉剑成天下惊。\n "
"                     十年铁杵磨成针，仗剑江湖自在行。\n"});
        story_msg+= ( {"飞雪连天射白鹿，笑书神侠倚碧鸳。\n "});
        story_msg+= ( {"少室山头琴未冷，风陵渡口似闻声。\n "
"                     人间自有情难老，不信娇女白发生。\n"});
        story_msg+= ( {"白马未驮夕照去，西风已送伤心来。\n "
"                     中原可有英雄泪，为洗秋兰带露开。\n"});
        story_msg+= ( {"灵枢终未得天枢，素问何曾问髯胡。\n "
"                     烛泪滴残海棠冷，忍听山歌到晓无？\n"});
        story_msg+= ( {"漫唱采茶觉已迟，犹怜深信未相欺。\n "
"                     世间多少痴情女，伤尽男儿不自知。\n"});
        story_msg+= ( {"燕子坞前从此醉，杏花林里向来痴。\n "
"                     红颜老去英雄在，落日牛羊归去迟。\n"});
        story_msg+= ( {"倦世何由惜此身，杨郎履下漫多尘。\n "
"                     人间自有花如雨，妾是花中第几人？ \n"});
        story_msg+= ( {"万骑却回千骑分，中原何计御胡尘？\n "
"                     世间一死宁无惧？君为家山我为君。\n"});
        story_msg+= ( {"来如流水逝如风，何处来兮何所终。\n "
"                     沧海茫茫挂帆去，天涯从此各西东。\n"});
        story_msg+= ( {"风中弱絮荡轻盈，赢得世间倾国名。\n "
"                     昨日江山今夜月，琵琶一曲唱生平。\n"});
        story_msg+= ( {"平生至乐在何处，平生至爱是何人？\n "
"                     一醉千杯君莫问，怜取姑射山中人。\n"});
        story_msg+= ({ "发现BUG请报告巫师，可以获得适当奖励。\n"
"                      隐瞒并利用BUG获利的，给予惩罚，甚至杀档处理。\n" });
        story_msg+=({"江湖自古多浩劫，杀机一现尸成野。\n"
"                      劝君未到功力老，勿动妄思问生死。\n"});


        story_msg_len=sizeof(story_msg);
        str=story_msg[random(story_msg_len)];

        message("channel:mess",sprintf(HIY"\n【典故】无名老人：%s\n" NOR, str),users());
        remove_call_out("story_check");
        call_out("story_check",300);
}

// 玩家之间的战斗奖励要写在这里set_override("die", func)
string ask_shengsi()
{   
        object me;
        string fam1,fam2,temp;
        int exp_rate,exp;
        me=this_player();

        if( query_temp("chousha/ask", me) )
                return CYN"你现在已经加入江湖了，你的敌对门派是"+query_temp("chousha/fam",me)+"赶快去吧！\n"NOR;

        if( query("chousha")<2 )
                return CYN"仇杀还没正式开始呢，先等一会吧！\n"NOR;    

        if( query("chousha")>3 )
                return CYN"你来太迟了，赶不上这次仇杀了，等下次吧！\n"NOR;

        if( query("combat_exp",me)<1000000 )
                return CYN"凭你现在这点本事，不相干的事还是不要多管的好！\n"NOR;

        if( query("score", me)<1000 )
                return CYN"你在江湖中的声望太低了，估计没有哪个门派会邀请你！\n"NOR;

        exp=query("combat_exp",me);
        temp=read_file("/quest/quest4/exp_rate",1,1);
        exp_rate=atoi(temp);
        if( !wizardp(me) && (exp_rate*exp_rate/4) < exp/100000 )
        {
              do{
                        exp_rate++;
                }       while( (exp_rate*exp_rate/4) < exp/100000 );

                temp=sprintf("%d",exp_rate);
                write_file("/quest/quest4/exp_rate",temp,1);  
        }

        fam1=read_file("/quest/quest4/fam1",1,1);
        fam2=read_file("/quest/quest4/fam2",1,1);

        if( query_temp("chousha/fam",me) )
        {
                set_temp("chousha/ask",1,me);
                command("chat "+query("name",me)+"加入江湖对付"+query_temp("chousha/fam",me)+"，生死由命，立状为凭！\n");

                if( query_temp("chousha/fam",me)==fam2 )
                {
                        set_temp("apply/short", 
                                ({HIW+fam1+"同道"NOR+HIG"   江湖义士   "NOR+query("name",me)+"("+query("id",me)+")"}),me);
                } 
                else if( query_temp("chousha/fam",me)==fam1 )
                {
                        set_temp("apply/short", 
                                ({CYN+fam2+"助拳"NOR+HIG"   江湖豪客   "NOR+query("name",me)+"("+query("id",me)+")"}),me);
                }
    
                call_out("heading_for",1,me);  
                return CYN"你立刻前往京城加入此次江湖，一切好自为之了！\n"NOR;    
        }

        if( query("shen",me) >= 200000 || (query("shen",me) > -200000 && random(2)) )  
        {
                set_temp("chousha/fam",fam2,me);
                delete_temp("apply/short",me);
                set_temp("apply/short", 
                        ({HIW+fam1+"同道"NOR+HIG"   江湖义士   "NOR+query("name",me)+"("+query("id",me)+")"}),me);
                command("chat "+query("name",me)+"加入江湖对付"+fam2+"，生死由命，立状为凭！\n");
        } else
        {
                set_temp("chousha/fam",fam1,me);
                delete_temp("apply/short",me);
                set_temp("apply/short", 
                        ({CYN+fam2+"助拳"NOR+HIG"   江湖豪客   "NOR+query("name",me)+"("+query("id",me)+")"}),me);
                command("chat"+query("name", me)+"加入江湖对付"+fam1+"，生死由命，立状为凭！\n");
        }

        set_temp("chousha/ask",1,me);
        call_out("heading_for",1,me);  
        return CYN"你立刻前往北京加入此次江湖，一切好自为之了！\n"NOR;
}


/*
string ask_zuji()
{
    object me;
    int exp_rate,exp;
    string temp;

    me=this_player();
    if( query_temp("zuji/ask", me) )
    return CYN"你现在已经加入阻击契丹武士了，赶快去吧！\n"NOR;   
  
    if( zuji_times < 1 )
    return CYN"现在江湖上好好的，你居心何在啊？！\n"NOR;

    if( zuji_times > 1 )
    return CYN"江湖英雄令发完了，正在准备中，你等会吧！\n"NOR;

    if( query("combat_exp", me)<1000000 )
    return CYN"你还是先学好本领再来吧！\n"NOR;

    if( query("score", me)<1000 )
    return CYN"你在江湖中的声望太低了，江湖英雄令你接不起啊！\n"NOR;

    exp=query("combat_exp", me);
    temp=read_file("/quest/quest4/killer_rate",1,1);
    exp_rate=atoi(temp);
    if( !wizardp(me) && (exp_rate*exp_rate/4) < exp/100000 )
    {
            do{
                  exp_rate++;
              } while( (exp_rate*exp_rate/4) < exp/100000 );

              temp=sprintf("%d",exp_rate);
              write_file("/quest/quest4/killer_rate",temp,1);
    }
    
    command("chat"+query("name", me)+"接下了"+HIW"江湖英雄令"
            +HIC"，对抗此次契丹武士，江湖各路同道共勉！\n"); 

    me->delte_temp("apply/short");
    me->set_temp("apply/short",
          ({HIR"英雄令使"NOR+me->name()+"("+query("id", me)+")"}));
    set_temp("zuji/ask", 1, me);

    return CYN"呵呵，又是一个不怕死的，武林有望啊，多加小心吧！\n"NOR;
}
*/


int heading_for(object me)
{
        string fam1,fam2;

        fam1=read_file("/quest/quest4/fam1",1,1);
        fam2=read_file("/quest/quest4/fam2",1,1); 

        if( objectp(me) && query_temp("chousha/fam",me) )
        {
                if( query_temp("chousha/fam",me) == fam2 )
                        me->move("/maze/jingcheng/juyi");
                else if( query_temp("chousha/fam",me) == fam1 )
                        me->move("/maze/jingcheng/yingxiong");
        }
        message_vision(YEL"$N一路马不停蹄，连夜赶到了紫金城！\n"NOR,me);
        return 1;
}
