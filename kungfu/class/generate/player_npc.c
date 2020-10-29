// person used in quest

inherit CLASS_D("generate") + "/chinese";
inherit F_SSERVER;

int  accept_object(object who, object ob);

void random_move();
int  leave();
int  is_stay_in_room()        { return 1; }

mapping family_punishers = ([
        "武当派"   : ({ CLASS_D("misc") + "/chongxu" }),
        "少林派"   : ({ CLASS_D("misc") + "/fangsheng" }),
        "华山派"   : ({ CLASS_D("misc") + "/murenqing" }),
        "峨嵋派"   : ({ CLASS_D("misc") + "/guoxiang" }),
        "桃花岛"   : ({ CLASS_D("misc") + "/taogu" }),
        "神龙教"   : ({ CLASS_D("misc") + "/zhong" }),
        "丐帮"     : ({ CLASS_D("misc") + "/wangjiantong" }),
        "古墓派"   : ({ CLASS_D("misc") + "/popo" }),
        "全真教"   : ({ CLASS_D("misc") + "/laodao" }),
        "星宿派"   : ({ CLASS_D("misc") + "/xiaoxian" }),
        "逍遥派"   : ({ CLASS_D("misc") + "/liqiushui" }),
        "大轮寺"   : ({ CLASS_D("misc") + "/laoseng" }),
        "血刀门"   : ({ CLASS_D("misc") + "/hongri" }),
        "灵鹫宫"   : ({ CLASS_D("misc") + "/tonglao" }),
        "慕容世家" : ({ CLASS_D("misc") + "/furen" }),
        "欧阳世家" : ({ CLASS_D("misc") + "/laonu" }),
        "关外胡家" : ({ CLASS_D("misc") + "/huyidao" }),
        "段氏皇族" : ({ CLASS_D("misc") + "/duansh" }),
        "明教"     : ({ CLASS_D("misc") + "/yangdingtian" }),
        "日月神教" : ({ CLASS_D("misc") + "/zhanglao" }),
        "魔教"     : ({ CLASS_D("misc") + "/jiaozhu" }),
]);

void create()
{
        ::create();
        set("gender",query("gender"));
        set("age", 30 + random(30));
        set("long", "");
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
        add_money("gold",2 + random(4));
}

void set_from_me(object me,int arg)
{
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        mapping skill_statusb;
        string *sname, *mname, *pname;
        string *snameb;
        object npc,weapon,punisher;

        int i, temp, myexp, mylvl, k, count, point, jieti;
        int skl_lvl;

        npc = this_object();

        if (arg == 1)
        {
                jieti=query("reborn/times", me);

                //五次解体以上的玩家，杀手来自各个门派
                // if (jieti >= 5 || "日月神教" == me->query("family/family_name"))
                if (1)
                        set("family/family_name", keys(family_punishers)[random(sizeof(family_punishers))], npc);
                else
                        set("family",query("family",  me), npc);

                if (mapp(skill_status = npc->query_skills()))
                {
                        skill_status = npc->query_skills();
                        sname = keys(skill_status);

                        temp = sizeof(skill_status);
                        for (i = 0; i < temp; i++)
                                npc->delete_skill(sname[i]);
                }

                if (mapp(map_status = npc->query_skill_map()))
                {
                        mname = keys(map_status);
                        temp = sizeof(map_status);
                        for (i = 0; i < temp; i++)
                                npc->map_skill(mname[i]);
                }

                if (mapp(prepare_status = npc->query_skill_prepare()))
                {
                        pname = keys(prepare_status);

                        temp = sizeof(prepare_status);
                        for(i = 0; i < temp; i++)
                                npc->prepare_skill(pname[i]);
                }

                if( !stringp(query("family/family_name", npc)) )
                        punisher = load_object("/kungfu/class/misc/lonely");
                else
                {
                        if( undefinedp(family_punishers[query("family/family_name", npc)]) )
                                punisher = me;
                        else
                        punisher=load_object(family_punishers[query("family/family_name", npc)][0]);
                        if (!objectp(punisher))
                                punisher = me;
                }

                skl_lvl = NPC_D->init_skill_level(me);
                if (skl_lvl < 100) skl_lvl = 100;
                if (mapp(skill_status = punisher->query_skills()))
                {
                        sname = keys(skill_status);
                        for (i = 0; i < sizeof(skill_status); i++)
                                // npc->set_skill(sname[i], skill_status[sname[i]]);
                                npc->set_skill(sname[i], skl_lvl);
                }

                if (mapp(map_status = punisher->query_skill_map()))
                {
                        mname = keys(map_status);
                        for(i = 0; i < sizeof(map_status); i++)
                                npc->map_skill(mname[i], map_status[mname[i]]);
                }


                if (mapp(prepare_status = punisher->query_skill_prepare()))
                {
                        pname = keys(prepare_status);
                        for(i = 0; i < sizeof(prepare_status); i++)
                                npc->prepare_skill(pname[i], prepare_status[pname[i]]);
                }

                /*
                if ( me->query_skill("qiankun-danuoyi",1) > 0)
                {
                        npc->set_skill("qiankun-danuoyi",1);
                        npc->map_skill("parry","qiankun-danuoyi");
                }

                if ( me->query_skill("douzhuan-xingyi",1) > 0)
                {
                        npc->set_skill("douzhuan-xingyi",1);
                        npc->map_skill("parry","douzhuan-xingyi");
                }

                if ( me->query_skill("taxue-wuhen",1) > 0)
                {
                        npc->set_skill("taxue-wuhen",1);
                        npc->map_skill("dodge","taxue-wuhen");
                }

                if ( me->query_skill("lingbo-weibu",1) > 0)
                {
                        npc->set_skill("lingbo-weibu",1);
                        npc->map_skill("dodge","lingbo-weibu");
                }
                */

                if ( jieti )
                        set("reborn/times", jieti, npc);

                if (punisher != me)
                        destruct(punisher);

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

                my["combat_exp"] = hp_status["combat_exp"];

                my["max_qi"]     *= 1.2;
                my["eff_qi"]     *= 1.2;
                my["qi"]         *= 1.2;
                my["max_jing"]   *= 1.4;
                my["eff_jing"]   *= 1.4;
                my["jing"]       *= 1.4;

                my["max_qi"]     += my["max_qi"]*jieti/10;
                my["eff_qi"]     += my["eff_qi"]*jieti/10;
                my["qi"]         += my["qi"]*jieti/10;
                my["max_jing"]   += my["max_jing"]*jieti/10;
                my["eff_jing"]   += my["eff_jing"]*jieti/10;
                my["jing"]       += my["jing"]*jieti/10;

                mylvl = 0;

                if( !query("reborn/times", me) )
                {
                        if ( mapp(skill_statusb = me->query_skills()) )
                        {
                                snameb = keys(skill_statusb);
                                for(k=0; k<sizeof(skill_statusb); k++)
                                {
                                        if (SKILL_D(snameb[k])->type() != "knowledge")
                                        {
                                                if ((int)me->query_skill(snameb[k],1) > mylvl)
                                                        mylvl = (int)me->query_skill(snameb[k],1);
                                        }
                                }
                        }
                        mylvl = mylvl * 9 / 10;
                } else
                        mylvl = to_int(pow(to_float(my["combat_exp"] / 100), 1.0 / 3)) * 10 + 1;

                if (mylvl < 200)
                        mylvl = 200;

                if ( mapp(skill_statusb = npc->query_skills()) ) {
                        snameb = keys(skill_statusb);
                        count = sizeof(skill_statusb);

                        for(k=0; k<sizeof(skill_statusb); k++) {
                                if (SKILL_D(snameb[k])->type() != "knowledge")
                                {
                                        if (snameb[k] == "poison")
                                                npc->set_skill(snameb[k],200);
                                        else
                                                npc->set_skill(snameb[k],mylvl);
                                }
                       }
                }

                my["jiali"] = npc->query_skill("force") / 2;

                if( objectp(weapon=query_temp("weapon", npc)) )
                        destruct(weapon);

                if( stringp(query("family/family_name", npc)) )
                switch(query("family/family_name", npc) )
                {
                        case "武当派":
                        case "华山派":
                        case "峨嵋派":
                        case "桃花岛":
                        case "全真教":
                        case "慕容世家":
                                weapon = new("/clone/weapon/changjian");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "日月神教":
                                weapon = new("/d/fuzhou/obj/xiuhua");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "大轮寺":
                                weapon = new("/clone/weapon/falun");
                                weapon->move(npc);
                                weapon->set_amount(4);
                                weapon->wield();
                                break;
                        case "关外胡家":
                        case "血刀门":
                                weapon = new("/clone/weapon/blade");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "星宿派":
                        case "神龙教":
                                weapon = new("/clone/weapon/gangzhang");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "古墓派":
                                weapon = new("/clone/weapon/gangjian");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                        case "少林派":
                                weapon = new("/clone/weapon/changbian");
                                weapon->move(npc);
                                weapon->wield();
                                break;
                } else {
                        string *lonelysword = ({
                                "staff",
                                "sword",
                                "hammer",
                                "club",
                                "dagger",
                                "blade",
                                "force",
                                "whip",
                                "throwing",
                                "unarmed",
                                "finger",
                                "claw",
                                "strike",
                                "hand",
                                "cuff"
                        });
                        set("can_perform/lonely-sword", lonelysword, npc);
                        set("can_perform/jiuyin-baiguzhao/shenzhao", 1, npc);
                        weapon = new("/clone/weapon/changjian");
                        weapon->move(npc);
                        weapon->wield();
                }
        }

        if( query("family/family_name", npc) )
                set("long","此人是"+query("family/family_name", npc)+"的杀手。\n");
        else
                set("long","此人是泥潭远古时代的创世神将！\n");

        npc->reset_action();

        return;
}

int accept_fight(object ob)
{
        object me;
        me = this_object();
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

        // NPC移到迷宫中，不需要随机走动了
        // NPC_D->random_move(this_object());
}

void destruct_me()
{
        message_vision("$N急急忙忙的走了。\n", this_object());
        destruct(this_object());
        return;
}
