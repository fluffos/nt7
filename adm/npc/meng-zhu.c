// This program is a part of XYZX MudLIB
// meng-zhu.c 武林盟主

#define WULIN DATA_DIR + "npc/meng-zhu"

#include <ansi.h>
inherit NPC;
inherit F_SAVE;
inherit F_NOCLONE;

string query_save_file()
{
        return WULIN;
}

void create()
{
        seteuid(getuid());
        if( !restore() ) {
                set_name("魏无双", ({ "wulin mengzhu", "mengzhu", "zhu" }) );
                set("title", "武林盟主" );
                set("gender", "男性" );
                set("age", 40);
                set("long","他就是雄踞武林，号召天下，威风赫赫的当今武林盟主。\n");
                set("attitude", "heroism");
                set("generation", 0);
                set("winner","NONE");
                set("str", 25);
                set("con", 25);
                set("int", 25);
                set("dex", 25);
                set("max_qi", 1500);
                set("eff_qi", 1500);
                set("qi", 1500);
                set("max_jing", 500);
                set("jing", 500);
                set("neili", 5000);
                set("max_neili", 500);
                set("jiali", 30);
                set("shen_type", 0);
                set("combat_exp", 800000);
                set("combat_exp", 15000000);
                set_skill("force",  700);
                set_skill("unarmed",700);
                set_skill("sword",  700);
                set_skill("bixie-jian",  450);
                set_skill("dodge",  700);
                set_skill("wudu-shengong",  700);
                set_skill("qianzhu-wandushou",  700);
                set_skill("parry",  700);
                map_skill("sword", "bixie-jian");
                map_skill("dodge", "bixie-jian");
                map_skill("parry", "bixie-jian");
                map_skill("force", "wudu-shengong");
                map_skill("unarmed", "qianzhu-wandushou");
                set("my_weapon", "/d/shaolin/obj/changjian");
                set("my_armor", "/d/city/obj/cloth");
                setup();
                carry_object("/d/shaolin/obj/changjian")->wield();
                carry_object("/d/city/obj/cloth")->wear();
        } else {
                if( !query("name") )
                        set_name("魏无双", ({  "wulin mengzhu", "mengzhu", "zhu" }));
                else
                        set_name(query("name"), ({  "wulin mengzhu", "mengzhu", "zhu" }));
                setup();
/*
                if( query("my_weapon") ) carry_object(query("my_weapon"))->wield();
                if( query("my_armor") )  carry_object(query("my_armor"))->wear();
*/
                UPDATE_D->check_user(this_object());
        }
        set("no_suck", 1);
        set("no_get", 1);
        set("auto_perform", 1);
        set("startroom", "/d/taishan/fengchan");
        check_clone();
}

void init()
{
        object me = this_object();
        object ob = this_player();

        add_action("do_kill", "kill");
        if( time()-query("combat/pktime", ob)<28800 )
                return;

        if( base_name(environment()) != query("startroom", me))return ;
        if( query("winner", me) == query("id", ob) && 
            query("age", me) <= query("age", ob) && 
            time()-query("recover", me)>60){
                set("eff_jing",query("max_jing",  ob), ob);
                set("jing",query("max_jing",  ob), ob);
                set("eff_qi",query("max_qi",  ob), ob);
                set("qi",query("max_qi",  ob), ob);
                if( query("neili", ob)<query("max_neili", ob) )
                        set("neili",query("max_neili",  ob), ob);
                if( query("jingli", ob)<query("max_jingli", ob) )
                        set("jingli",query("max_jingli",  ob), ob);
                set("recover", time(), me);
        }
        add_action("do_recopy",  "recopy");
        //add_action("do_recover", "recover");
}

int do_kill(string arg)
{
        object ob;
        int i;

        if( !this_object()->id(arg) ) return 0;
        if( query("winner", this_object()) == query("id", this_player()) )
                return notify_fail("你是不是疯了？！\n");

        command("say 你想谋害本盟主，当真是吃了熊心豹子胆了！！");
        command("say 座下白衣武士何在！");

        message_vision("四周的白衣武士群起对$N发动攻击！\n", this_player());
        for( i=0; i<4; i++ ) {
                if( objectp( ob = present("wei shi " + (i+1), environment(this_object())) ) )
                        ob->kill_ob(this_player());
                else    this_object()->kill_ob(this_player());
        }
        return 1;
}

int accept_fight(object ob)
{
        object me  = this_object();

        if( time()-query("combat/pktime", this_player())<28800 )
                return 0;
        if( query("winner", me) == query("id", ob)){
                command("say 你跟你自己打什么架？！\n");
                return 0;
        }

        if( wizardp(this_player()) ){
                command("say 巫师不能抢盟主之位！\n");
                return 0;
        }

        if( me->is_fighting() || query("fighting", me)){
                command("say 已经有人正在挑战武林盟主！\n");
                return 0;
        }

        full_self();
        competition_with(ob);

        return 1;
}

void win()
{
        object me = query_competitor();

        if( !objectp(me) ) {
                command("heihei");
                return;
        }

        command("say 看来" + RANK_D->query_respect(me) +
                "还得多加练习，方能在当今武林中出人头地 !\n");
        ::win();
}

void lost()
{
        object me, ob;

        me = this_object();
        ob = query_competitor();

        if( !living(me) ) me->revive();
        command("say 果然厉害，恭喜你成为当今武林盟主！\n");
        command("chat 哈哈哈，到底是长江後浪推前浪，一代新人换旧人！\n");
        command("chat恭喜"+query("name", ob)+"被推举为当今武林盟主！\n");
        set("fighting", 1, me);
        remove_call_out("do_copy");
        call_out("do_copy", 1, me, ob);

        ::lost();
}

int do_copy(object me, object ob)
{
        object shizhe,room;
        string name;

        if( !(shizhe = find_living("shangshan shizhe")) )
                shizhe = load_object(SHANGSHAN);
        name=query("winner", shizhe);
        if( query("id", ob) == name){
                shizhe->rm_file();
                if( !room = find_object("/d/taishan/xiayi") )
                        room = load_object("/d/taishan/xiayi");
                room->reset();
        }

        if( !(shizhe = find_living("fae shizhe")) )
                shizhe = load_object(FAE);
        name=query("winner", shizhe);
        if( query("id", ob) == name){
                shizhe->rm_file();
                if( !room = find_object("/d/taishan/zhengqi") )
                        room = load_object("/d/taishan/zhengqi");
                room->reset();
        }

        seteuid(getuid());
        if( !living(me) ) me->revive();
        set("winner",query("id",  ob), me);
        addn("generation", 1, me);
        set("name",query("name",  ob), me);

        delete("party", ob);
        set("party/party_name", YEL+"第"+chinese_number(query("generation", me))+"代"+NOR, ob);
        set("party/rank", YEL+"武林盟主"+NOR, ob);

        set("short", YEL+"第"+chinese_number(query("generation", me))+"代武林盟主"+NOR+""+query("name", me)+"(Wulinmengzhu)", me);
        delete("title", me);
        remove_call_out("do_clone");
        call_out("do_clone", 0, me, ob);
        return 1;
}

int do_recopy(object me, object ob)
{
        me = this_object();
        ob = this_player();

        if( me->is_fighting() || ob->is_fighting() || query("fighting", me) )
                return notify_fail("现在这里正打的不亦乐乎！等会吧！\n");

        if( query("winner", me) != query("id", ob) )
                return notify_fail("你不是现任武林盟主！\n");;

        set("name",query("name",  ob), me);
        delete("party", ob);
        set("party/party_name", YEL+"第"+chinese_number(query("generation", me))+"代"+NOR, ob);
        set("party/rank", YEL+"武林盟主"+NOR, ob);

        set("short", YEL+"第"+chinese_number(query("generation", me))+"代武林盟主"+NOR+""+query("name", me)+"(Wulinmengzhu)", me);
        delete("title", me);
        remove_call_out("do_clone");
        call_out("do_clone", 0, me, ob);
        return 1;
}

int do_clone(object me, object ob)
{
        object *inv/*, newob*/,weapon;
        mapping hp_status, skill_status, map_status;
        string *sname, *mname;
        int i, temp;
        string skill1,skill2;

        seteuid( geteuid(me) );
        if( !living(me) ) me->revive();

        /* delete and copy skills */
        if( mapp(skill_status = me->query_skills()) ) {
                sname  = keys(skill_status);
                temp = sizeof(skill_status);
                for( i=0; i<temp; i++ ) {
                        me->delete_skill(sname[i]);
                }
        }
        if( mapp(skill_status = ob->query_skillc()) ) {
                sname  = keys(skill_status);
                for( i=0; i<sizeof(skill_status); i++ ) {
                        me->set_skill(sname[i], skill_status[sname[i]]);
                }
        }

        /* delete and copy skill maps */
        if( mapp(map_status = me->query_skill_map()) ) {
                mname  = keys(map_status);
                temp = sizeof(map_status);
                for( i=0; i<temp; i++ ) {
                        me->map_skill(mname[i]);
                }
        }
        if( mapp(map_status = ob->query_skill_map()) ) {
                mname  = keys(map_status);
                for( i=0; i<sizeof(map_status); i++ ) {
                        me->map_skill(mname[i], map_status[mname[i]]);
                }
        }

        /* unwield and remove weapon & armor */
        inv = all_inventory(me);
        for( i=0; i<sizeof(inv); i++ ) {
                destruct(inv[i]);
        }
        set("my_weapon", 0);
        set("my_armor", 0);
        /* wield and wear weapon & armor */
        inv = all_inventory(ob);
        for( i=0; i<sizeof(inv); i++ ) {
                if( query("weapon_prop/damage", inv[i])>100
                 || query("armor_prop/armor", inv[i])>100
                 || query("shaolin", inv[i] )
                 || query("value", inv[i])>100000)continue;

                if( query("weapon_prop", inv[i]) && query("equipped", inv[i])){
                        //carry_object(base_name(inv[i]))->wield();
                        set("my_weapon", base_name(inv[i]), me);
                }
                else if( query("armor_prop", inv[i]) && query("equipped", inv[i])){
                        //carry_object(base_name(inv[i]))->wear();
                        set("my_armor", base_name(inv[i]), me);
                }
        }

        /* copy entire dbase values */
        hp_status = ob->query_entire_dbase();
        set("str", hp_status["str"], me);
        set("int", hp_status["int"], me);
        set("con", hp_status["con"], me);
        set("dex", hp_status["dex"], me);
        set("age", hp_status["age"], me);
        set("max_qi", hp_status["max_qi"], me);
        set("eff_qi", hp_status["eff_qi"], me);
        set("qi", hp_status["qi"], me);
        set("max_jing", hp_status["max_jing"], me);
        set("eff_jing", hp_status["eff_jing"], me);
        set("jing", hp_status["jing"], me);
        set("max_neili", hp_status["max_neili"], me);
        set("neili", 2*hp_status["max_neili"], me);
        set("max_jingli", hp_status["max_jingli"], me);
        set("jingli", hp_status["jingli"], me);
        set("jiali", hp_status["jiali"], me);
        set("gender", hp_status["gender"], me);
        set("combat_exp", hp_status["combat_exp"], me);
        set("birthday", hp_status["birthday"], me);

        if( objectp(weapon=query_temp("weapon", me))){
                skill1=query("skill_type", weapon);
                if( objectp(weapon=query_temp("secondaly_weapon", me)) )
                        skill2=query("skill_type", weapon);
        }

        if( mapp(skill_status = me->query_skills()) ) {
                sname  = keys(skill_status);
                for( i=0; i<sizeof(skill_status); i++ ) {
                        command("enable unarmed "+sname[i]);
                        command("enable force "+sname[i]);
                        command("enable parry "+sname[i]);
                        command("enable dodge "+sname[i]);
                        if (stringp(skill1))
                                command("enable "+skill1+" "+sname[i]);
                        if (stringp(skill2))
                                command("enable "+skill2+" "+sname[i]);
                }
        }

        command("enforce max");

        delete("fighting", me);
        set("backup/condition", ob->query_condition(), me);
        save();
        tell_object(ob, "状态储存完毕。\n");
        /*
        newob = new(MENGZHU);
        newob->move("/d/taishan/fengchan");
        destruct(me);
        */
        return 1;
}

int do_recover()
{
        object me, ob;
        mapping skill_status, map_status;
        string *sname, *mname;
        int i;
        mapping cnd;
        string *ks;

        me = this_object();
        ob = this_player();

        if( me->is_fighting() || ob->is_fighting() || query("fighting", me) )
                return notify_fail("现在这里正打的不亦乐乎！等会吧！\n");

        if( query("winner", me) != query("id", ob) || query("age", me)>query("age", ob) || 
             query("birthday", me) != query("birthday", ob) )
                return notify_fail("你不是现任武林盟主！\n");

        if( time()-query("recover", me)<60 )
                return notify_fail("状态暂时不能复元。\n");

        /* delete and copy skills */
        if( mapp(skill_status = ob->query_skills()) ) {
                sname  = keys(skill_status);
                for(i=0; i<sizeof(skill_status); i++) {
                        ob->delete_skill(sname[i]);
                }
        }

        if( mapp(skill_status = me->query_skills()) ) {
                sname  = keys(skill_status);
                for( i=0; i<sizeof(skill_status); i++ ) {
                        ob->set_skill(sname[i], skill_status[sname[i]]);
                }
        }

        /* delete and copy skill maps */
        if( mapp(map_status = ob->query_skill_map()) ) {
                mname  = keys(map_status);
                for( i=0; i<sizeof(map_status); i++ ) {
                        ob->map_skill(mname[i]);
                }
        }

        if( mapp(map_status = me->query_skill_map()) ) {
                mname  = keys(map_status);
                for( i=0; i<sizeof(map_status); i++ ) {
                        ob->map_skill(mname[i], map_status[mname[i]]);
                }
        }

        /* copy combat exp values */
        set("combat_exp",query("combat_exp",  me), ob);
        cnd=query("backup/condition", me);
        if( mapp(cnd) && sizeof(cnd) ) {
        ks = keys(cnd);
        for( i=0;i<sizeof(ks);i++ )
                ob->apply_condition(ks[i], cnd[ks[i]]);
        }

        set("recover", time(), me);
        write("状态复元完毕。\n");
        return 1;
}