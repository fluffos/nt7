// /d/yixing/npc/bangzhu.h
// Last Modified by Lonely on Jul. 12 2002
#include <ansi.h>
#include <dbase.h>
#include <login.h>
#include <move.h>

void init()
{
        object ob = this_player();

        ::init();

        if( !is_fighting() && interactive(ob) )
        {
                remove_call_out("checking");
                call_out("checking", 1, ob);
        }

        add_action("do_check", "exert");
        add_action("do_check", "yun");
        add_action("do_xue", "xue");
}

void checking(object ob)
{
        object me = this_object();

        if( !living(me) || is_fighting() ) return;
        if( environment() != environment(ob) ) return;
        if( query("party/party_name", ob) == query("party/party_name") )
        {
                message_vision("$N拍了拍$n的头说道：加油！长乐帮发了自有你的好处！\n", me, ob);
                return;
        }
        if( !random(2) )
                message_vision("$N双手抱拳，牛里牛气地说道：见到本帮主，难道没有任何表示吗？\n", me);
        else message_vision("$N说道：还不赶快加入" + query("party/party_name") + "！！！\n", me);
}

int do_check(string arg)
{
        string what, who;

        if( !arg ) return notify_fail("");
        if( arg != "play" )
        {
                 if( sscanf(arg, "%s %s", what, who) != 2 )
                        return notify_fail("");
                 if( what != "play" ) return notify_fail("");
        }
        call_other(BANGSKILLS+"/play2", "exert", this_player(), this_player());
        return 1;
}

int ask_join()
{
        object ob = this_player(), obj;
        string myfam, ob_fam;
        int exp=query("combat_exp", ob);

        ob_fam=query("family/family_name", ob);
        if( ob_fam == "丐帮" )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "一定是丐帮派来卧底的吧！\n");
                return 1;
        }
        if( ob_fam == "大理段家" )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "一定是大理国派来卧底的吧！\n");
                return 1;
        }

        if( ob_fam == "桃花岛" )
        {
                say(name() + "说道：贵派祖师黄药师一向不与江湖人士往来，我怎么能随便收容他老人家的门下！\n");
                return 1;
        }

        if( ob_fam == "武当派" || ob_fam == "峨嵋派" || ob_fam == "华山派" ||
                 ob_fam == "少林派" || ob_fam == "南少林派" )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "一定是名门正派派来卧底的吧！\n");
                return 1;
        }
        myfam = (string)query("party/party_name");
        if( query("party/party_name", ob) == myfam )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "！竟敢开帮主的玩笑！！！\n");
                return 1;
        }
        if( exp > query("combat_exp") && !wizardp(ob))
        {
                say(name()+"双手一抱拳道："+RANK_D->query_respect(ob)+ "莫非是开玩笑吧。\n");
                return 1;
        }
        if( time()<query("party/enter_time", ob)+600 )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "，你如此反复无常岂能容身于江湖！！！\n");
                return 1;
        }
        message_vision("$N重重地拍了一下$n的肩膀，喝道：好样的！从今以后跟兄弟们有难同当！\n", this_object(), ob);

        set_temp("apply/short", ({ HIR + myfam + "帮众"NOR + query("name",ob)+"("+capitalize(query("id",ob))+")" }), ob);
        delete("party", ob);
        set("party/party_name", myfam, ob);
        set("party/rank", "帮众", ob);
        set("party/enter_time", time(), ob);
        if( obj = present("bang ling", ob) ) destruct(obj);

        obj = new(BANGLING);
        set("owner",query("id",  ob), obj);
        set("fam", myfam, obj);
        set("combat_exp", query("combat_exp"), obj);
        set("long", "这是"+myfam+"的帮令，上面刻着「"+query("name", ob)+"」。\n", obj);
        obj->move(ob);
        message_vision("$N把一"+query("unit", obj)+obj->name()+"扔给$n。\n",this_object(),ob);
        log_file("partyjoin",sprintf("%s于%s时加入%s\n",query("name", ob),ctime(time()),myfam));
        return 1;
}

// duty 2 teach skills

string ask_skills()
{
        object ling, me = this_player();
        int amount;

        if( is_fighting() )
                return RANK_D->query_rude(me) + "瞎了眼没见我正忙着？！";

        if( query("party/party_name", me) != query("party/party_name") )
                return RANK_D->query_rude(me) + "莫非是想打听我帮的秘密吧。";

        if( !(ling = present("bang ling", me)) )
                return RANK_D->query_rude(me) + "竟连自己的帮令都管不住！";

        if( query("owner", ling) != query("id", me) )
                return RANK_D->query_rude(me) + "竟连自己的帮令都管不住！";

        if( (amount=query("score", ling))<10 )
                return RANK_D->query_rude(me)+"再加把劲，帮主才会指点你一下！";

        if( amount > 100 )
        {
                set("party/skills_asked", 100, me);
                addn("score", -100, ling);
        } else {
                set("party/skills_asked", amount, me);
                delete("score", ling);
        }

        tell_object(me, "请键入：武功的英文名字。\n");
        return "好吧。";
}

int do_xue(string arg)
{
        object me = this_player();
        string *sname;
        int i, amount, level, mylvl;

        if( !(amount=query("party/skills_asked", me)) )
        {
                write("你还没征求帮主同意呢。\n");
                return 1;
        }

        if( is_fighting() )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(me) + "瞎了眼没见我正忙着？！");
                return 1;
        }
        if( !arg )
        {
                sname = keys(query_skills());
                write("\n" + name() + "所学过的技能：\n\n");
                for(i = 0; i < sizeof(sname); i++)
                        write(to_chinese(sname[i]) + " (" + sname[i] + ")" + "\n");
                return 1;
        }
        if( (level = (int)query_skill(arg, 1)) < 1 )
        {
                say(name() + "摇了摇头道：帮主没学过。\n");
                return 1;
        }

        mylvl = (int)me->query_skill(arg, 1);
        if( level < mylvl )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(me) + "居然超过老子了。\n");
                return 1;
        }
        if( mylvl > 80 )
        {
                say(name() + "摇了摇头道：你得去门派中正式拜师才能继续提高" + to_chinese(arg) + "。\n");
                return 1;
        }
        if( query("jing", me)+10<query("max_jing", me) )
        { 
                write("你先歇会儿吧。\n");
                return 1;
        }
        set("jing", 10, me);
        me->improve_skill(arg,amount*query("int", me)/3);
        delete("party/skills_asked", me);
        message_vision("$N向$n请教有关「" + to_chinese(arg) + "」的疑问。\n", me, this_object());
        tell_object(me, "你听了帮主的指导，对「" + to_chinese(arg) + "」似乎有些心得。\n");
        return 1;
}

// duty 3 died to give bangyin

void die()
{
        object ob, corpse, killer;

        if( !living(this_object()) ) revive(1);
//        clear_condition();

        if( objectp(killer = query_temp("last_damage_from")) )
        {
                ob = new(BANGYIN);
                set("long", query("fam")+query("name", ob)+"。\n", ob);
                ob->move(environment());
                message_vision(HIR"\n突然从$N衣袋中掉下一"+query("unit", ob)+ob->name()+"。\n"NOR,this_object());
                set_temp("my_killer",query("id", killer));
                set("my_killer",query("id",  killer), ob);
                set("combat_exp", query("combat_exp"), ob);
        }
        COMBAT_D->announce(this_object(), "dead");
        if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
                corpse->move(environment());
        remove_all_killer();
        all_inventory(environment())->remove_killer(this_object());

        dismiss_team();
        destruct(this_object());
}
