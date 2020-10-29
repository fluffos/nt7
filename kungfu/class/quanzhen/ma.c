// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_me();
string ask_miji();
mixed ask_skill1();
mixed ask_skill2();
string ask_array();
string ask_shu();
void create()
{
        set_name("马钰", ({"ma yu", "ma"}));
        set("gender", "男性");
        set("age", 42);
        set("class", "taoist");
        set("nickname",MAG"丹阳子"NOR);
        set("long",
                "他就是王重阳的大弟子，全真七子之首，丹阳子马钰马真人。\n"
                "他慈眉善目，和蔼可亲，正笑着看着你。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 30);

        set("title","全真七子之首");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 2200);
        set("max_jing", 2200);
        set("neili", 4700);
        set("max_neili", 4700);
        set("jiali", 100);
        set("level", 18);
        set("combat_exp", 1400000);

        set_skill("force", 180);
        set_skill("quanzhen-xinfa", 180);
        set_skill("sword", 170);
        set_skill("quanzhen-jian",170);
        set_skill("dodge", 180);
        set_skill("jinyan-gong", 180);
        set_skill("parry", 180);
        set_skill("literate",100);
        set_skill("strike", 180);
        set_skill("chongyang-shenzhang", 180);
        set_skill("haotian-zhang", 180);
        set_skill("finger",180);
        set_skill("zhongnan-zhi", 180);
        set_skill("taoism",150);
        set_skill("medical", 210);
        set_skill("liandan-shu", 210);
        set_skill("cuff",200);
        set_skill("whip",200);
        set_skill("chunyang-quan",200);
        set_skill("duanyun-bian",200);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("miji_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
                "秘籍" : (: ask_miji :),
                "金雁功" : (: ask_me :),
                "金雁图谱" : (: ask_me :),
                "鹰飞雁舞" : (: ask_skill1 :),
                "天罡北斗阵" : (: ask_array :),
                "北斗七星阵" : (: ask_array :),
                "秘籍"      : (: ask_shu :),
                "鞭法总诀"   : (: ask_shu :),
                "shu" : (: ask_shu :),
                "玄门金锁" : (: ask_skill2 :),
        ]) );

        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/weapon/changjian");
        carry_object(__DIR__"obj/greenrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 100 )
        {
                command("say 你的本门内功心法火候不足,难以领略更高深的武功。");
                return;
        }
        if( query("shen", ob)<10000 )
        {
                command("say 行侠仗义我辈学武人需铭记在心，这点你做的可不够啊！\n");
                return;
        }
        command("pat"+query("id", ob));
        command("say 好吧，我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "全真教" )
                return RANK_D->query_respect(this_player()) +
                "与本教毫无瓜葛，我教的武功典籍可不能交给你。";
        if (query("book_count") < 1)
                return "你来晚了，金雁图谱已经被人取走了。";
        addn("book_count", -1);
        ob = new("/clone/book/jinyantu");
        ob->move(this_player());
        return "好吧，这本「金雁图谱」你拿回去好好研读。";

}
string ask_shu()
{
        object ob;

        if( query("family/master_id", this_player()) != "mayu" )
                return RANK_D->query_respect(this_player()) +
                "非我弟子，不知此话从何谈起？";
        if (query("shu_count") < 1)
                return "你来晚了，本派的秘籍不在此处。";
        addn("shu_count", -1);
        ob = new("/clone/book/whip");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"拿到鞭法总诀啦。\n");
        return "好吧，这本「鞭法总诀」你拿回去好好钻研。";
}
string ask_miji()
{
        mapping fam;
        object ob, *obs,ob2 ;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "全真教" )
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";

        if (query("miji_count") < 1)
                return "你来晚了，本派的鞭法秘籍不在此处。";

        obs = filter_array(children("/d/quanzhen/obj/whip_book"), (: clonep :));
                  if (sizeof(obs) > 5)
                return "你来晚了，本派的鞭法秘籍不在此处。";

        ob=new("/d/quanzhen/obj/whip_book");
        ob->move(this_player());
        addn("miji_count", -1);
        // command ("rumor "+this_player()->query("name")+"弄到了一册丹阳鞭法谱。");
        return "好吧，这本「丹阳鞭法谱」你拿回去好好钻研。";
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/jinyan-gong/yanwu", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("jinyan-gong", 1) < 1)
                return "你连金雁功都没学，何谈绝招可言？";

        if( query("family/gongji", me)<50 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<3000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("jinyan-gong", 1) < 60)
                return "你的金雁功不够娴熟，练高点再来吧。";

        if (me->query_skill("force") < 80)
                return "你的内功修为不够，修炼高后再来找我吧。";

        message_sort(HIY "\n$n" HIY "对$N" HIY "点了点头，当下更不答"
                     "话，但见身影时如鹰击长空、时如群雁飞舞，令人眼"
                     "花撩乱，煞是好看。\n\n" NOR, me,
                     this_object());

        command("nod");
        command("say 这招很简单，稍加练习便成。");
        tell_object(me, HIC "你学会了「鹰飞雁舞」。\n" NOR);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("jinyan-gong"))
                me->improve_skill("jinyan-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinyan-gong/yanwu", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/jinguan-yusuo/suo", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("jinguan-yusuo", 1) < 1)
                return "你连金关玉锁都没学，何谈绝招可言？";

        if( query("family/gongji", me)<400 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<50000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("jinguan-yusuo", 1) < 150)
                return "你的金关玉锁不够娴熟，练高点再来吧。";

        if (me->query_skill("force") < 200)
                return "你的内功修为不够，修炼高后再来找我吧。";

        message_sort(HIY "\n$n" HIY "点了点头，说道：“我给你演示一遍，可"
                     "看仔细了。”只听$n" HIY "话音刚落，顿时起身而立，双"
                     "手蓦的回圈，暗含天罡北斗星位，朝$N" HIY "攻去。霎时"
                     "$N" HIY "只觉招数一紧，接着双臂瘫软，全身力道竟似被"
                     "$n" HIY "锁住一般。\n\n" NOR, me, this_object()); 

        command("nod");
        command("say 这招看似简单，实却艰奥无比，你自行体会吧。");
        command("say 日后行走江湖，切记得饶人处且饶人，莫要积仇过深。");
        tell_object(me, HIC "你学会了「玄门金锁」。\n" NOR);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("jinguan-yusuo"))
                me->improve_skill("jinguan-yusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinguan-yusuo/suo", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
string ask_array()
{
        object room, qizi, obj, ob = this_player(), me = this_object();
        mapping ob_fam, skl;
        string *skillname;
        int i;

        ob_fam=query("family", ob);
        skl = ob->query_skills();

        if (sizeof(skl) <= 1)
                return RANK_D->query_respect(ob) +
                "功力不够，不够资格闯天罡北斗阵。";
        if( query("score", ob)<20000 )
                return RANK_D->query_respect(ob) +
                "阅历不足，不够资格闯天罡北斗阵。";

        skillname  = keys(skl);
        for(i=0; i<sizeof(skl); i++) {
                if ((skl[skillname[i]] < 80) || (sizeof(skl) == 0))
                return RANK_D->query_respect(ob) +
                "功力不够，不够资格闯天罡北斗阵。";
        }
        if( query("qixing", ob) )
                return RANK_D->query_respect(ob) +
                "已然闯过天罡北斗阵，可不要拿老道开这等玩笑。";
/*
        if ( ob_fam["family_name"] != "全真教" || ob_fam["generation"] != 3)
                return RANK_D->query_respect(ob) + "，你没资格闯天罡北斗阵。";
*/
        if( query("assigned_qixing", me) )
                return RANK_D->query_respect(ob) + "，今日有人挑战天罡北斗阵，你过一段时间再来吧。";

        set("assigned_qixing",query("id",  ob), me);
        command("smile");
        say("\n马钰道长说道：好吧，我去召集众师弟。稍候在大校场上等你。\n");
        message_vision("\n马钰道长往南离开。\n\n", ob);

/* 谭处端 */
        if(!( room = find_object("/d/quanzhen/rongwutang")) )
                room = load_object("/d/quanzhen/rongwutang");
                  me->move(room);
        if( !objectp(obj = present("tan chuduan", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n马钰道长走了过来。\n\n", ob);
                return "真是对不起，全真七子有人不在，无法布天罡北斗阵。\n";
        }
        message("vision","\n马钰道长走了过来，跟谭处端说了几句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "谭处端点了点头，快步跟了出去。\n", room, obj);

/* 刘处玄 */
        if(!( room = find_object("/d/quanzhen/jingxiushi")) )
                room = load_object("/d/quanzhen/jingxiushi");
                  me->move(room);
        if( !objectp(obj = present("liu chuxuan", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n马钰道长走了过来。\n\n", ob);
                return "真是对不起，全真七子有人不在，无法布天罡北斗阵。\n";
        }
        message("vision","\n马钰道长走了过来，跟刘处玄说了几句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "刘处玄点了点头，快步跟了出去。\n", room, obj);

/* 丘处机 */
        if(!( room = find_object("/d/quanzhen/laojundian")) )
                room = load_object("/d/quanzhen/laojundian");
                  me->move(room);
        if( !objectp(obj = present("qiu chuji", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n马钰道长走了过来。\n\n", ob);
                return "真是对不起，全真七子有人不在，无法布天罡北斗阵。\n";
        }
        message("vision","\n马钰道长走了过来，跟丘处机说了几句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "丘处机点了点头，快步跟了出去。\n", room, obj);

/* 王处一 */
        if(!( room = find_object("/d/quanzhen/wanwutang")) )
                room = load_object("/d/quanzhen/wanwutang");
                  me->move(room);
        if( !objectp(obj = present("wang chuyi", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n马钰道长走了过来。\n\n", ob);
                return "真是对不起，全真七子有人不在，无法布天罡北斗阵。\n";
        }
        message("vision","\n马钰道长走了过来，跟王处一说了几句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "王处一点了点头，快步跟了出去。\n", room, obj);

/* 郝大通 */
        if(!( room = find_object("/d/quanzhen/guangning")) )
                room = load_object("/d/quanzhen/guangning");
                  me->move(room);
        if( !objectp(obj = present("hao datong", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n马钰道长走了过来。\n\n", ob);
                return "真是对不起，全真七子有人不在，无法布天罡北斗阵。\n";
        }
        message("vision","\n马钰道长走了过来，跟郝大通说了几句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "郝大通点了点头，快步跟了出去。\n", room, obj);

/* 孙不二 */
        if(!( room = find_object("/d/quanzhen/qingjing")) )
                room = load_object("/d/quanzhen/qingjing");
                  me->move(room);
        if( !objectp(obj = present("sun buer", room) ))
        {
                me->move("/d/quanzhen/shiweishi");
                message_vision("\n马钰道长走了过来。\n\n", ob);
                return "真是对不起，全真七子有人不在，无法布天罡北斗阵。\n";
        }
        message("vision","\n马钰道长走了过来，跟孙不二说了几句。\n", room, obj);
        obj->move("/d/quanzhen/daxiaochang");
        message("vision", "孙不二点了点头，快步跟了出去。\n", room, obj);
        set_temp("pre_qixing", 1, ob);

        me->move("/d/quanzhen/daxiaochang");
        call_out("waiting", 1, me,1);
        return "好！大家都出来了。\n";
}

int waiting(object me,int wait_time)
{
        object ob;

        if( wait_time == 300 )
        {
                say( "马钰说道：看来他不会来了，我们回去罢！\n\n");
                call_out("do_back", 0, me);
                addn("score", -5000, me);
        }
        else if( !objectp(ob=present(query("assigned_qixing", me),environment(me))) )
        {
                wait_time++;
                call_out("waiting", 1, me,wait_time);
        }
        else call_out("preparing", 0, me, ob);

        return 1;
}

int preparing(object me, object ob)
{
        object *obs, room, obj1, obj2, obj3, obj4, obj5, obj6;
        string myname=query("name", me);
        int i;

        if(!( room = find_object("/d/quanzhen/daxiaochang")) )
        room = load_object("/d/quanzhen/daxiaochang");
        if(!objectp( obj1 = present("tan chuduan", environment(me))))
                return notify_fail("二师弟怎么不在？\n");
        if(!objectp( obj2 = present("liu chuxuan", environment(me))))
                return notify_fail("三师弟怎么不在？\n");
        if(!objectp( obj3 = present("qiu chuji", environment(me))))
                return notify_fail("四师弟怎么不在？\n");
        if(!objectp( obj4 = present("wang chuyi", environment(me))))
                return notify_fail("五师弟怎么不在？\n");
        if(!objectp( obj5 = present("hao datong", environment(me))))
                return notify_fail("六师弟怎么不在？\n");
        if(!objectp( obj6 = present("sun buer", environment(me))))
                return notify_fail("小师妹怎么不在？\n");

        me->dismiss_team();
        me->set_leader();
        me->add_team_member(obj1);
        me->add_team_member(obj2);
        me->add_team_member(obj3);
        me->add_team_member(obj4);
        me->add_team_member(obj5);
        me->add_team_member(obj6);

        say( "马钰说道：不相干的人，如不欲观摩天罡北斗阵，请即刻离开。\n");


  obs=me->query_team();
        for(i=0;i<sizeof(obs);i++)
        {
                ob->fight_ob(obs[i]);
                obs[i]->fight_ob(ob);
                if(obs[i] != me)
                        message_vision(myname+"道："+query("name", obs[i])+"请做好准备！\n",me);
        }
//        command("say chat " + ob->query("title") + ob->query("name") +
//                "于今日" + NATURE_D->game_time() + "挑战全真天罡北斗阵！\n");
        message("channel:snow",HIC"【闯阵】马钰[Mayu]："+query("title", ob)+query("name", ob)+
                HIC+"于今日" + NATURE_D->game_time() + "挑战全真天罡北斗阵！\n"NOR,users());
        say(HIC"马钰吟道：“一住行窝几十年。”\n");
        say("谭处端吟道：“蓬头长日走如颠。”\n");
        say("刘处玄吟道：“海棠亭下重阳子。”\n");
        say("丘处机接口道：“莲叶舟中太乙仙。”\n");
        say("王处一吟道：“无物可离虚壳外。”\n");
        say("郝大通吟道：“有人能悟未生前。”\n");
        say("孙不二吟道：“出门一笑无拘碍。”\n");
        say("马钰收句道：“云在西湖月在天！”\n\n\n"NOR);

        message_vision(myname+ "清了清喉咙，大声说道：好，时辰已到，现在开始启动「天罡北斗阵」！\n",me);
        message_vision(myname+ "突然身形移动，发动众全真弟子抢占位置，左边四人，右边三人，正是摆的「天罡北斗阵」阵法。\n",me);
        say("马钰位当天枢，谭处端位当天璇，刘处玄位当天玑，丘处机位当天权，四人组成斗魁；\n");
        say("王处一位当玉衡，郝大通位当开阳，孙不二位当摇光，三人组成斗柄。\n");
        remove_call_out("do_qixing");
        call_out("do_qixing", 2, me, ob);
        return 1;
}


int do_qixing(object me, object en)
{
        object *obs, weapon, enweapon;
        int i, j, power;
        string err;
        string *where = ({
                "天枢",
                "天璇",
                "天玑",
                "天权",
                "玉衡",
                "开阳",
                "摇光"
        });

        if(pointerp(obs=me->query_team()) )
        switch (random (4))
        {
                case 0:
message_vision("天罡北斗阵气势宏大，前攻后击，连环相接，让人眼花撩乱，方寸顿失。\n",me);
                        break;
                case 1:
message_vision("天罡北斗阵法滚滚推动，攻势连绵不绝，瞬间将敌人围在垓心。\n",me);
                        break;
                case 2:
message_vision("天罡北斗阵越缩越小，无形剑气象浪潮一般逼向中央，令人有窒息之感。\n",me);
                        break;
                case 3:
message_vision("只见天罡北斗阵暗合五行八卦之理，阵中人步法精妙，攻守配合得天衣无缝，威力之大，让人叹为观止。\n",me);
                        break;
        }
        for(i=0;i<sizeof(obs);i++)
        {
                weapon=query_temp("weapon", obs[i]);
                power = obs[i]->query_skill("force",1)/10;
          addn_temp("apply/attack", power, obs[i]);
          addn_temp("apply/damage", power, obs[i]);
                switch (random(2))
                {
                        case 0:
message_vision("\n"+where[i]+"位上的"+query("name", obs[i])+"气沉丹田，暗运神功，猛然吐气开声，身形往前一纵,但见",me);
                                break;
                        case 1:
message_vision("\n"+where[i]+"位上的"+query("name", obs[i])+"挺身而出，步法精妙，长袖飘飘，攻势如虹。只见",me);
                                break;
//                       default:
                }
          err=catch(COMBAT_D->do_attack(obs[i],en,weapon,0));
          if (err)
          {
                  message("channel:debug","天罡北斗阵攻击出错 err="+err,users());
                  return 1;
          }
                addn_temp("apply/attack", -power, obs[i]);
                addn_temp("apply/damage", -power, obs[i]);
                if( query("qi", en)*2 <= query("max_qi", en) )
                {
                        en->remove_all_enemy();
                        remove_call_out("do_end");
                        call_out("do_end", 1, me, en, 0);
                        return 1;
                }
        }
        j = random(sizeof(me->query_team()));
        enweapon=query_temp("weapon", en);
        if (enweapon)
          COMBAT_D->do_attack(en,obs[j], enweapon);
        else
          COMBAT_D->do_attack(en,obs[j], enweapon);
        if( query("qi", obs[j])*2 <= query("max_qi", obs[j]) )
        {
                message_vision(HIR+query("name", obs[j])+"一跤趴在地上，摔出北斗阵。\n"NOR,me);
                en->remove_all_enemy();
                remove_call_out("do_end");
                call_out("do_end", 1, me, en, 1);
                return 1;
        }
        else if( query("qi", obs[j])*3 <= query("max_qi", obs[j])*2 )
        {
                message_vision(query("name", obs[j])+"踉跄了一步，差点摔出北斗阵。\n",me);
        }
        else if( query("qi", obs[j])*5 <= query("max_qi", obs[j])*4 )
                message_vision(query("name", obs[j])+"被打得晃了几晃，不过又站稳了步子。\n",me);

        remove_call_out("do_qixing");
        call_out("do_qixing", 1, me, en);
        return 1;
}
int do_end(object me, object en, int result)
{
        if( result == 1)
        {
                if( query_temp("pre_qixing", en) )
                {
                        set("qixing", 1, en);
                }
                delete_temp("pre_qixing", en);
                addn("combat_exp", 50000, en);
                addn("score", 30000, en);
                addn("potential", 10000, en);
                message_vision(HIR"\n天罡北斗阵被"+query("name", en)+"打破了。\n\n"NOR,me);
                message("channel:snow",HIR"【通告】"HIY+query("name", en)+"打破天罡北斗阵了！\n"NOR,users());
        }
        else
        {
                delete_temp("pre_qixing", en);
                message("channel:snow",HIR"【通告】"HIY+query("name", en)+"没能闯出天罡北斗阵！\n"NOR,users());
    message_vision(HIR"\n$N笑了笑：天罡北斗阵不愧为全真镇教之宝。\n"NOR,me);
                addn("score", -3000, en);
        }
        remove_call_out("do_back");
        call_out("do_back", 1, me);
        return 1;
}
int do_back(object me)
{
        object *obs, weapon;
        int i;

        if(pointerp(obs=me->query_team()) )
        {
                for(i=0;i<sizeof(obs);i++)
                {
                        if( objectp(weapon=query_temp("weapon", obs[i]) )
                                 && query("skill_type", weapon) == "sword" )
message_vision("$N身子向后一纵，使一招『收剑式』，将剑挽了一个剑花，往怀中一抱，退出「天罡北斗阵」。\n", obs[i]);
                        else
message_vision("$N身子向后一纵，使一招『收山式』，右拳划了一圈，左掌往怀中一抱，退出「天罡北斗阵」。\n", obs[i]);

message_vision("$N作了个楫道：贫道先告退了！说完就快步离开了。\n", obs[i]);
                        if( query("name", obs[i]) == "马钰" )
                                obs[i]->move("/d/quanzhen/shiweishi");
                        if( query("name", obs[i]) == "谭处端" )
                                obs[i]->move("/d/quanzhen/rongwutang");
                        if( query("name", obs[i]) == "刘处玄" )
                                obs[i]->move("/d/quanzhen/jingxiushi");
                        if( query("name", obs[i]) == "丘处机" )
                                obs[i]->move("/d/quanzhen/laojundian");
                        if( query("name", obs[i]) == "王处一" )
                                obs[i]->move("/d/quanzhen/wanwutang");
                        if( query("name", obs[i]) == "郝大通" )
                                obs[i]->move("/d/quanzhen/guangning");
                        if( query("name", obs[i]) == "孙不二" )
                                obs[i]->move("/d/quanzhen/qingjing");
                }
        }///d/quanzhen/shiweishi
        me->dismiss_team();
}
