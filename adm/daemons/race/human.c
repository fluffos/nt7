// human.c
// From ES2
// Modified by Xiang@XKX

// A normal human is at least 40 kg weight
#define BASE_WEIGHT 40000

inherit F_DBASE;
inherit F_SKILL;

mapping *combat_action = ({
([      "action":               "$N挥拳攻击$n的$l",
        "damage_type":  "瘀伤",
]),
([      "action":               "$N往$n的$l一抓",
        "damage_type":  "抓伤",
]),
([      "action":               "$N往$n的$l狠狠地踢了一脚",
        "damage_type":  "瘀伤",
]),
([      "action":               "$N提起拳头往$n的$l捶去",
        "damage_type":  "瘀伤",
]),
([      "action":               "$N对准$n的$l用力挥出一拳",
        "damage_type":  "瘀伤",
]),
});

void create()
{
        seteuid(getuid());
}

void setup_human(object ob)
{
        mapping my;
        int s;
        int x, y;
        int limit;
        int xism_age;
        int skill;
        int jing_age;
        int add_point;
        int die_point;
        int r;

        my = ob->query_entire_dbase();
        ob->set_default_action(__FILE__, "query_action");
	set("default_actions", (: call_other, __FILE__, "query_action" :), ob);
        if (! stringp(my["unit"])) my["unit"] = "位";
        if (! stringp(my["gender"])) my["gender"] = "男性";
        if (/*undefinedp*/!(my["can_speak"])) my["can_speak"] = 1;
        if (! stringp(my["attitude"])) my["attitude"] = "peaceful";
        if (! pointerp(my["limbs"])) my["limbs"] = ({
                "头部", "颈部", "胸口", "后心", "左肩", "右肩", "左臂",
                "右臂", "左手", "右手", "两肋", "左脸", "腰间", "小腹",
                "左腿", "右腿", "右脸", "左脚", "右脚", "左耳", "右耳"
        });

        if (/*undefinedp*/!(my["age"])) my["age"] = 14;
        if (/*undefinedp*/!(my["str"])) my["str"] = 10 + random(21);
        if (/*undefinedp*/!(my["con"])) my["con"] = 10 + random(21);
        if (/*undefinedp*/!(my["dex"])) my["dex"] = 10 + random(21);
        if (/*undefinedp*/!(my["int"])) my["int"] = 10 + random(21);
        if (/*undefinedp*/!(my["per"])) my["per"] = 10 + random(21);
        if (/*undefinedp*/!(my["kar"])) my["kar"] = 10 + random(21);

        if (!userp(ob) && /*undefinedp*/!(my["max_jingli"]))
        {
                limit=query("combat_exp", ob)/1000;
                my["max_jingli"] = limit;
                my["jingli"] = limit;
        }

        if (userp(ob) || ob->is_baby() || /*undefinedp*/!(my["max_jing"]))
        {
                s = ob->query_int()*5 + ob->query_con()+ob->query_dex()+ob->query_str();
                my["max_jing"] = 100;
                if (/*undefinedp*/!(my["born"]))
                        ; else
                if (my["age"] < 11)
                        my["max_jing"] = 50 + my["age"] * s * 2 / 3;
                else
                if (my["age"] < 24)
                        my["max_jing"] += (my["age"] - 11) * s * 2 / 3;
                else
                        my["max_jing"] += (24 - 11) * s * 2 / 3;

                if ((int)my["max_jingli"] > 0)
                        my["max_jing"] += (int)my["max_jingli"] / 3;

                // 佛家养精：３０岁前补精，３０岁后长精
                if (userp(ob) && mapp(my["family"])) {
                        if ( my["family"]["family_name"] == "峨嵋派" )
                                xism_age = (int)ob->query_skill("mahayana", 1);
                        else if ( my["family"]["family_name"] == "少林派" )
                                xism_age = (int)ob->query_skill("buddhism", 1);
                        else if ( my["family"]["family_name"] == "段氏皇族" )
                                xism_age = (int)ob->query_skill("buddhism", 1);
                        else if ( my["family"]["family_name"] == "雪山寺" || my["family"]["family_name"] == "血刀门" || my["family"]["family_name"] == "密宗" )
                                xism_age = (int)ob->query_skill("lamaism", 1);
                }
                else
                        xism_age = 0;

                if (xism_age > 250) xism_age = 250;

                if (xism_age > 39) {
                        xism_age = xism_age/2;
                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = ob->query_skill("force");
                        if (xism_age > 0 && skill > 0) {
                                skill = xism_age * (skill/20);
                                if ( my["family"]["family_name"] == "少林派" )
                                {
                                        my["max_jing"] += skill;
                                        //my["max_qi"] += skill/2;
                                }
                                else if ( my["family"]["family_name"] == "峨嵋派" )
                                {
                                        my["max_jing"] += skill;
                                        //my["max_qi"] += skill/2;
                                }
                                else if ( my["family"]["family_name"] == "段氏皇族" )
                                {
                                        my["max_jing"] += skill*2/3;
                                        //my["max_qi"] += skill/2;
                                }
                                else
                                {
                                        my["max_jing"] += skill*3/4;
                                        //my["max_qi"] += skill/2;
                                }
                        }
                }

                // 地刹炼魂：每死一次，丐帮精长根骨值
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "丐帮")
                {
                        add_point = my["combat_exp"]/50000;
                        if (mapp(my["combat"]))
                        {
                                die_point = my["combat"]["dietimes"];
                                if (die_point > add_point) die_point = add_point;

                                if (die_point < 100)
                                        my["max_jing"] += ob->query_con() * die_point * 10;
                                else
                                        my["max_jing"] += ob->query_con() * 100 * 10;
                        }
                }

                // 华山紫霞神功；３０岁前补精，３０岁后长精
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "华山派"
                && (jing_age = (int)ob->query_skill("zixia-shengong", 1)/3) > 39)
                {
                        if (jing_age > 250) jing_age = 250;
                        jing_age = jing_age/2;

                        if (my["age"] <= 30) jing_age -= my["age"];
                        else jing_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if ( jing_age > 0 )
                                my["max_jing"] += jing_age * (skill/30);
                }

                // 古墓素女心法；３０岁前补精，３０岁后长精
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "古墓派"
                        && (jing_age =(int)ob->query_skill("yunv-xinjing", 1)) > 39)
                {
                        if (jing_age > 250) jing_age = 250;
                        jing_age = jing_age/2;

                        if (my["age"] <= 30) jing_age -= my["age"];
                        else jing_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if ( jing_age > 0 )
                                my["max_jing"] += jing_age * (skill/30);
                }

                // 桃花岛奇门五行：３０岁前补精，３０岁后长精，但效用小
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "桃花岛"
                        && (xism_age=(int)ob->query_skill("qimen-wuxing", 1)/3) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if (xism_age > 0 ) my["max_jing"] += xism_age * (skill/35);
                }

                // 明教圣火玄冥：３０岁前补精，３０岁后长精，但效用小
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "明教"
                        && (xism_age=(int)ob->query_skill("shenghuo-shengong", 1)/3) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if (xism_age > 0 ) my["max_jing"] += xism_age * (skill/35);
                }

                // 日月神教日月光华：３０岁前补精，３０岁后长精，但效用小
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "日月神教"
                        && (xism_age=(int)ob->query_skill("riyue-guanghua", 1)/3) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if (xism_age > 0 ) my["max_jing"] += xism_age * (skill/35);
                }

                // 关外胡家妙手驱毒：３０岁前补精，３０岁后长精，但效用小
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "关外胡家"
                        && (xism_age=(int)ob->query_skill("dispel-poison", 1)) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if (xism_age > 0 ) my["max_jing"] += xism_age * (skill/35);
                }

                if ((userp(ob) || ob->is_baby()) && my["breakup"])
                        my["max_jing"] += my["max_jing"];

                if ((userp(ob) || ob->is_baby()) && my["animaout"])
                        my["max_jing"] += my["max_jing"];

#ifdef DB_SAVE
                if (userp(ob) && MEMBER_D->is_valid_member(ob))
                        my["max_jing"] += my["max_jing"] / 2;
#endif

                if( (userp(ob) || ob->is_baby()) && (r=ob->query_skill("qingmu-zhenqi", 1)) ) {
                        r /= 250;
                        r += 1;
                        if (r > 1000) {
                                r -= (r / 1000);
                                if (r > 5000) 
                                        r -= (r / 5000);
                        }
                        my["max_jing"] += my["max_jing"] / 4 * r;
                }

                if( (userp(ob) || ob->is_baby()) && (r=query("xuemai_level", ob)) )
                        my["max_jing"] += my["max_jing"] * r;

                if( userp(ob) && (r=query("reborn/times", ob)) )
                        my["max_jing"] += my["max_jing"] * r;

                my["max_jing"] += ob->query_all_buff("max_jing");
                my["max_jing"] += my["max_jing"]*ob->query_ability_buff("max_jing")/100;
        }

        if (userp(ob) || ob->is_baby() || /*undefinedp*/!(my["max_qi"]))
        {
                s = ob->query_con()*5 + ob->query_str() + ob->query_con() + ob->query_dex();
                my["max_qi"] = 100;
                if (/*undefinedp*/!(my["born"]))
                        ; else
                if (my["age"] < 11)
                        my["max_qi"] = 60 + my["age"] * my["con"] / 2;
                else
                if (my["age"] < 27)
                        my["max_qi"] += (my["age"] - 11) * s * 2 / 3;
                else
                        my["max_qi"] += (27 - 11) * s * 2 / 3;

                if ((int)my["max_neili"] > 0)
                        my["max_qi"] += (int)my["max_neili"] / 4;

                // 武当太极加气
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "武当派" &&
                    (x = (int)ob->query_skill("taoism", 1)) > 39 &&
                    (y = (int)ob->query_skill("taiji-shengong", 1)) > 39)
                {
                        if (x > 350) x = (x - 350) / 2 + 350;
                        if (y > 350) y = (y - 350) / 2 + 350;
                        if (x > 200) x = (x - 200) / 2 + 200;
                        if (y > 200) y = (y - 200) / 2 + 200;

                        my["max_qi"] += (x + 100 ) * (y + 100) / 100;
                }

                //全真先天功加气
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "全真教" &&
                    (x = (int)ob->query_skill("taoism", 1)) > 39 &&
                    (y = (int)ob->query_skill("xiantian-gong", 1)) > 39)
                {
                        if (x > 350) x = (x - 350) / 2 + 350;
                        if (y > 350) y = (y - 350) / 2 + 350;
                        if (x > 200) x = (x - 200) / 2 + 200;
                        if (y > 200) y = (y - 200) / 2 + 200;

                        my["max_qi"] += (x + 100 ) * (y + 100) / 100;
                }

                // 星宿聚毒练气：３０岁前补气，３０岁后长气
                if (userp(ob) &&  mapp(my["family"]) && my["family"]["family_name"] == "星宿派"
                && (xism_age=(int)ob->query_skill("poison", 1)/3) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("huagong-dafa",1);

                        if (xism_age > 0 )
                                my["max_qi"] += xism_age * (skill/30);
                }

                // 白驼山庄聚毒练气：３０岁前补气，３０岁后长气
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "欧阳世家"
                     && (xism_age=(int)ob->query_skill("poison", 1)/3) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;
                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("hamagong",1);

                        if (xism_age > 0 )
                                my["max_qi"] += xism_age * (skill/30);
                }

                // 逍遥派逍遥奇学练气：３０岁前补气，３０岁后长气
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "逍遥派"
                     && (xism_age=(int)ob->query_skill("xiaoyao-qixue", 1)) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if (xism_age > 0 )
                                my["max_qi"] += xism_age * (skill/40);
                }

                // 灵鹫宫八荒神功：３０岁前补气，３０岁后长气
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "灵鹫宫"
                     && (xism_age=(int)ob->query_skill("bahuang-gong", 1)/3) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("force",1);

                        if (xism_age > 0 )
                                my["max_qi"] += xism_age * (skill/40);
                }

                // 慕容世家紫徽心法练气：３０岁前补气，３０岁后长气
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "慕容世家"
                     && (xism_age=(int)ob->query_skill("zihui-xinfa", 1)/3) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if (xism_age > 0 )
                                my["max_qi"] += xism_age * (skill/40);
                }

                // 神龙岛神龙迷辛练气：３０岁前补气，３０岁后长气
                if (userp(ob) && mapp(my["family"]) && my["family"]["family_name"] == "神龙教"
                     && (xism_age=(int)ob->query_skill("shenlong-mixin", 1)) > 39)
                {
                        if (xism_age > 250) xism_age = 250;
                        xism_age = xism_age/2;

                        if (my["age"] <= 30) xism_age -= my["age"];
                        else xism_age -= 30;

                        skill = (int)ob->query_skill("force");

                        if (xism_age > 0 )
                                my["max_qi"] += xism_age * (skill/50);
                }

                if ((userp(ob) || ob->is_baby()) && my["breakup"])
                        my["max_qi"] += my["max_qi"] * 2;

#ifdef DB_SAVE
                if (userp(ob) && MEMBER_D->is_valid_member(ob))
                        my["max_qi"] += my["max_qi"] / 2;
#endif

               if( (userp(ob) || ob->is_baby()) && (r=ob->query_skill("houtu-shengong", 1)) ) {
                        r /= 250;
                        r += 1;
                        if (r > 1000) {
                                r -= (r / 1000);
                                if (r > 5000) 
                                        r -= (r / 5000);
                        }
                        my["max_qi"] += my["max_qi"] / 3 * r;
                }

                if( (userp(ob) || ob->is_baby()) && (r=query("xuemai_level", ob)) )
                        my["max_qi"] += my["max_qi"] * r;

                if( userp(ob) && (r=query("reborn/times", ob)) )
                        my["max_qi"] += my["max_qi"] * r;

                // 服用super药品
                if( (userp(ob) || ob->is_baby()) && query("drug_addqi", ob) )
                        my["max_qi"] += query("drug_addqi", ob);

                my["max_qi"] += ob->query_all_buff("max_qi");
                my["max_qi"] += my["max_qi"]*ob->query_ability_buff("max_qi")/100;
        }

        if (! ob->query_weight())
                ob->set_weight((BASE_WEIGHT + (my["str"] - 10) * 2000) * 7 / 10);
}

mapping query_action()
{
        return combat_action[random(sizeof(combat_action))];
}
