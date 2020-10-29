// person used in quest

inherit CLASS_D("generate") + "/chinese";
inherit F_SSERVER;

int  accept_object(object who, object ob);

void random_move();
int  leave();
void check_quest(object ob);
int  is_stay_in_room()        { return 1; }

void create()
{
        ::create();
        set("gender",query("gender"));
        set("age", 30 + random(30));
        if (arrayp(query("from")) && sizeof(query("from")))
                set("long",query("from")[random(sizeof(query("form")))] + "\n");
        else
                set("long","");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set("scale", 150);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 50);
        set_temp("born_time", time());
        add_money("silver",20);
        keep_heart_beat();
}

void set_from_me(object me,int arg)
{
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        mapping skill_statusb;
        string *sname, *mname, *pname;
        string *snameb;
        object npc,weapon;

        int i, temp, mylvl, k, count, point;
        int myexp;

        npc = this_object();

        set("family",query("family",  me), npc);

        if (mapp(skill_status = npc->query_skills()))
        {
                skill_status = npc->query_skills();
                sname = keys(skill_status);

                temp = sizeof(skill_status);
                for (i = 0; i < temp; i++)
                        npc->delete_skill(sname[i]);
        }

        if (mapp(skill_status = me->query_skills()))
        {
                skill_status = me->query_skills();
                sname = keys(skill_status);

                for (i = 0; i < sizeof(skill_status); i++)
                        npc->set_skill(sname[i], skill_status[sname[i]]);
        }

        if (mapp(map_status = npc->query_skill_map()))
        {
                mname = keys(map_status);
                temp = sizeof(map_status);
                for (i = 0; i < temp; i++)
                        npc->map_skill(mname[i]);
        }

        if (mapp(map_status = me->query_skill_map()))
        {
                mname = keys(map_status);
                for(i = 0; i < sizeof(map_status); i++)
                        npc->map_skill(mname[i], map_status[mname[i]]);
        }

        if (mapp(prepare_status = npc->query_skill_prepare()))
        {
                pname = keys(prepare_status);

                temp = sizeof(prepare_status);
                for(i = 0; i < temp; i++)
                        npc->prepare_skill(pname[i]);
        }

        if (mapp(prepare_status = me->query_skill_prepare()))
        {
                pname = keys(prepare_status);

                for(i = 0; i < sizeof(prepare_status); i++)
                        npc->prepare_skill(pname[i], prepare_status[pname[i]]);
        }

        if (arg == 1)
        {
        hp_status = me->query_entire_dbase();
        my = npc->query_entire_dbase();

        my["str"] = hp_status["str"];
        my["int"] = hp_status["int"];
        my["con"] = hp_status["con"];
        my["dex"] = hp_status["dex"];

                my["qi"] = my["eff_qi"] = my["max_qi"] = hp_status["max_qi"];
                my["jing"] = my["eff_jing"] = my["max_jing"] = hp_status["max_jing"];
                my["jingli"] = my["eff_jingli"] = my["max_jingli"] = hp_status["max_jingli"];
                my["neili"] = my["max_neili"]  = hp_status["max_neili"];
                my["jiali"] = npc->query_skill("force") / 2;

                my["max_qi"]     *= 1.2;
                my["eff_qi"]     *= 1.2;
                my["qi"]         *= 1.2;
                my["max_jing"]   *= 1.2;
                my["eff_jing"]   *= 1.2;
                my["jing"]       *= 1.2;

                myexp=query("combat_exp", npc);
                myexp = myexp / 1000;

                if (myexp>80000) myexp = 80000;
                myexp *= 1000;
                mylvl = to_int(pow(myexp*10,0.33333)+1);

                mylvl = mylvl * 9 / 10;

                if ( mapp(skill_statusb = npc->query_skills()) ) {
                        snameb = keys(skill_statusb);
                        count = sizeof(skill_statusb);

                        for(k=0; k<sizeof(skill_statusb); k++) {
                                if (SKILL_D(snameb[k])->type() != "knowledge")
                                        npc->set_skill(snameb[k],mylvl);
                        }
                }
        }

        if( objectp(weapon=query_temp("weapon", npc)) )
                destruct(weapon);

        if( query_temp("weapon", me) )
        {
                switch(query_temp("weapon",query("skill_type",  me)) )
                {
                        case "sword" :
                                weapon = new("/clone/weapon/changjian");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "blade" :
                                weapon = new("/clone/weapon/blade");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "axe" :
                                weapon = new("/clone/weapon/axe");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "hammer" :
                                weapon = new("/clone/weapon/hammer");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "staff" :
                                weapon = new("/clone/weapon/gangzhang");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "whip" :
                                weapon = new("/clone/weapon/changbian");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                }
        }

        set("combat_exp", myexp, npc);

        npc->reset_action();

        return;
}

int accept_fight(object ob)
{
        object me;
        me = this_object();
        check_quest(ob);
        command("say 你给我去死吧！");
        command("yun powerup");
        command("yun shield");
        switch (me->query_skill_mapped("force"))
        {
                case "linji-zhuang":
                        command("yun tiandi");
                        command("yun daxiao");
                        set("qi",query("max_qi",  me), me);
                        set("jing",query("max_jing",  me), me);
                        break;
                case "huagong-dafa":
                        command("yun hua");
                        break;
                case "zixia-shengong":
                        command("yun ziqi");
                        break;
                case "huntian-qigong":
                        command("yun haixiao");
                        command("yun shengang");
                        break;
                case "bibo-shengong":
                        command("yun wuzhuan");
                        break;
                case "yunv-xinfa":
                        command("yun wang");
                        break;
                case "nuhai-kuangtao":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang":
                        command("yun longxiang");
                        command("yun panlong");
                        command("yun tunxiang");
                        break;
                case "hamagong":
                        command("yun reserve");
                        break;
                case "lengyue-shengong":
                        command("yun freeze");
                        break;
                case "kurong-xinfa":
                        command("yun kurong");
                        break;
        }
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        object me;
        me = this_object();
        check_quest(ob);
        command("say 你给我去死吧！");
        command("yun powerup");
        command("yun shield");
        switch (me->query_skill_mapped("force"))
        {
                case "linji-zhuang":
                        command("yun tiandi");
                        command("yun daxiao");
                        set("qi",query("max_qi",  me), me);
                        set("jing",query("max_jing",  me), me);
                        break;
                case "huagong-dafa":
                        command("yun hua");
                        break;
                case "zixia-shengong":
                        command("yun ziqi");
                        break;
                case "huntian-qigong":
                        command("yun haixiao");
                        command("yun shengang");
                        break;
                case "bibo-shengong":
                        command("yun wuzhuan");
                        break;
                case "yunv-xinfa":
                        command("yun wang");
                        break;
                case "nuhai-kuangtao":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang":
                        command("yun longxiang");
                        command("yun panlong");
                        command("yun tunxiang");
                        break;
                case "hamagong":
                        command("yun reserve");
                        break;
                case "lengyue-shengong":
                        command("yun freeze");
                        break;
                case "kurong-xinfa":
                        command("yun kurong");
                        break;
        }
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        object me;
        me = this_object();
        check_quest(ob);
        command("say 你给我去死吧！");
        command("yun powerup");
        command("yun shield");
        switch (me->query_skill_mapped("force"))
        {
                case "linji-zhuang":
                        command("yun tiandi");
                        command("yun daxiao");
                        set("qi",query("max_qi",  me), me);
                        set("jing",query("max_jing",  me), me);
                        break;
                case "huagong-dafa":
                        command("yun hua");
                        break;
                case "zixia-shengong":
                        command("yun ziqi");
                        break;
                case "huntian-qigong":
                        command("yun haixiao");
                        command("yun shengang");
                        break;
                case "bibo-shengong":
                        command("yun wuzhuan");
                        break;
                case "yunv-xinfa":
                        command("yun wang");
                        break;
                case "nuhai-kuangtao":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang":
                        command("yun longxiang");
                        command("yun panlong");
                        command("yun tunxiang");
                        break;
                case "hamagong":
                        command("yun reserve");
                        break;
                case "lengyue-shengong":
                        command("yun freeze");
                        break;
                case "kurong-xinfa":
                        command("yun kurong");
                        break;
        }
        kill_ob(ob);
        return 1;
}

void random_move()
{
        object me,target;
        if (time() - query_temp("born_time") > 900)
        {
              remove_call_out("destruct_me");
              call_out("destruct_me",1);
              return;
        }

        me = this_object();
        target = offensive_target(me);

        if( target
        &&      target->is_character()
        &&      me->is_fighting(target) )
        {
                check_quest(target);
        }
        NPC_D->random_move(this_object());
}

void destruct_me()
{
        message_vision("$N急急忙忙的走了。\n", this_object());
        destruct(this_object());
        return;
}

void check_quest(object ob)
{
        mapping quest;
        if( query("quest_dg", ob) )
                quest=query("quest_dg", ob);
        else if( query("quest_kh", ob) )
                quest=query("quest_kh", ob);
        else if( query("quest_hs", ob) )
                quest=query("quest_hs", ob);
        else if( query("quest_sn", ob) )
                quest=query("quest_sn", ob);

        if (!mapp(quest)) return;
        if (quest["type"] == "杀" && quest["name"] == this_object()->name())
                set_from_me(ob,2);

        return;
}