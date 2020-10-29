// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit BOSS;

void set_from_me(object me);
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
]);

void create()
{
        set_name("牢头", ({ "lao tou" }));
        //set("title", BLU "无恶不做" NOR);
        set("title", BLU "小魔王" NOR);
        set("long", "监狱里的牢头。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);
        
        set("max_qi", 8000000);
        set("max_jing", 5000000);
        set("neili", 20000000);
        set("max_neili", 100000);
        set("jiali", 20000);
        set("combat_exp", 150000000);
        set("level", 30);
        set("score", 50000);


        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        
        set_temp("apply/attack", 1400);
        set_temp("apply/armor", 3000);
        set_temp("apply/damage", 1600);
        set_temp("apply/unarmed_damage", 1600);
        set_temp("apply/add_xuruo", 60);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 20);
        set_temp("apply/add_busy", 5);
        
        set("clear_fuben", 1);
        set("auto_perform", 1);
        set("bonus", 10000);
        set("drops", ([ 
                "RA&RANDOM40"                                    :       10000,  // 低级普通装备
                "RA&RANDOM50"                                    :       300,    // 中级普通装备
                "FI&/clone/enchase/rune16"      : 500,
                "FI&/clone/enchase/rune17"      : 500,
                "MO&A3000"       :       300,
                "MO&A3001"       :       300,
                "MO&A3002"       :       300,
                "MO&A3003"       :       300,
                "MO&A3004"       :       300,
                "MO&A3005"       :       300,
                "MO&A3006"       :       300,
                
        ]));
        
        set("no_corpse", 1);
        setup();
        add_money("gold", 20 + random(10));
}

void init()
{
        object me;

        ::init();
        if (! interactive(me = this_player()) || 
            this_object()->is_fighting())
                return;

        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

void set_from_me(object me)
{
        mapping hp_status, skill_status, map_status, prepare_status;
        mapping my;
        object npc,weapon,punisher;
        string *sname, *mname, *pname;
        int i, skl_lvl;

        npc = this_object();

        set("family/family_name", keys(family_punishers)[random(sizeof(family_punishers))], npc);

        punisher = get_object(family_punishers[query("family/family_name")][0], npc);
        
        skl_lvl = NPC_D->init_skill_level(me) + 800;

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

        if ( me->query_skill("qiankun-danuoyi",1) > 0)
        {
                npc->set_skill("qiankun-danuoyi",skl_lvl);
                npc->map_skill("parry","qiankun-danuoyi");
        }

        if ( me->query_skill("douzhuan-xingyi",1) > 0)
        {
                npc->set_skill("douzhuan-xingyi",skl_lvl);
                npc->map_skill("parry","douzhuan-xingyi");
        }

        if ( me->query_skill("lingbo-weibu",1) > 0)
        {
                npc->set_skill("lingbo-weibu",skl_lvl);
                npc->map_skill("dodge","lingbo-weibu");
        }
        
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

        my["max_qi"]     += my["max_qi"]/10;
        my["eff_qi"]     += my["eff_qi"]/10;
        my["qi"]         += my["qi"]/10;
        my["max_jing"]   += my["max_jing"]/10;
        my["eff_jing"]   += my["eff_jing"]/10;
        my["jing"]       += my["jing"]/10;

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
        }

        npc->reset_action();

        return;
}

int accept_fight(object ob)
{
        object me;
        me = this_object();
        set_from_me(ob);
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
                case "surge-force":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang-gong":
                        command("yun longxiang-gong");
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
        set_from_me(ob);
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
                case "surge-force":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang-gong":
                        command("yun longxiang-gong");
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
        set_from_me(ob);
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
                case "surge-force":
                        command("yun haixiao");
                        break;
                case "xiantian-gong":
                        command("yun chunyang");
                        break;
                case "longxiang-gong":
                        command("yun longxiang-gong");
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

varargs void die(object killer)
{
        object *obs, env;
        object me, ob;
        object boss, maze_target, maze_door;
        int exp, pot, mar;
        string mazename;
        mapping maze;

        me = this_object();
        
        if (objectp(ob = previous_object(0)) && 
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                me->full_self();
                return;
        }
        
        env = environment(me);
        
        if (! killer) 
                killer = me->query_last_damage_from();
                
        if (objectp(killer))
        {
                obs = pointerp(killer->query_team()) ? 
                                killer->query_team() : ({ killer });
                obs = filter_array(obs, (: environment($1) == $(env) :));
                
                exp=query("bonus", me);
                pot = exp / 2;
                mar = pot / 2;
                foreach (object user in obs)
                        GIFT_D->bonus(user, ([ 
                                "exp" : exp, "pot" : pot, "mar" : mar ]));   
        }

        boss = new("/maze/prison/npc/yanfei"); 
        maze_target = MAZE_D->create_maze(boss); 
        boss->move(maze_target); 
        mazename=query("maze/mazename", maze_target);
        maze = MAZE_D->query_maze(mazename);       
        maze_door = new("/clone/misc/maze_door2");
        set("maze_entry", file_name(maze["entry"]), maze_door);
        maze_door->move(environment(this_object()));

        return ::die(killer);
}

void unconcious()
{
        object ob;

        if (objectp(ob = previous_object(0)) && 
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                this_object()->recover();
                return;
        }
        
        die();
}
