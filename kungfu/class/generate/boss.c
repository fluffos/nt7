// This program is a part of NITAN MudLIB
// chan_cler 中国挑战者 
   
int is_boss() { return 1; } 
inherit BOSS;

private void from_wudang(); 
private void from_shaolin(); 
private void from_huashan(); 
private void from_ouyang(); 
private void from_gaibang(); 
private void from_taohua(); 
private void from_gumu(); 
private void from_xingxiu(); 
private void from_xueshan(); 
private void from_xuedao(); 
private void from_xiaoyao(); 
private void from_shenlong(); 
private void from_emei();
private void from_quanzhen(); 
private void from_mingjiao();
private void from_lingjiu(); 
private void from_murong(); 
private void from_duanshi(); 
private void from_hujia(); 

/*  
function *init_family = ({ (: from_wudang :),   (: from_shaolin :),   (: from_huashan :), 
                           (: from_ouyang :),   (: from_gaibang :),   (: from_taohua :), 
                           (: from_gumu :),     (: from_xingxiu :),   (: from_xueshan :), 
                           (: from_xuedao :),   (: from_xiaoyao :),   (: from_shenlong :), 
                           (: from_emei :),     (: from_quanzhen :),  (: from_mingjiao :), 
                           (: from_lingjiu :),  (: from_murong :),    (: from_duanshi :),
                           (: from_hujia :),                      
                        }); 

void create() 
{ 
        NPC_D->generate_cn_name(this_object()); 
        set("long", "一个人。\n"); 
        set("gender", "男性"); 
        set("age", 20); 
        set("str", 20); 
        set("int", 20); 
        set("con", 20); 
        set("dex", 20); 
        
        // the follow 5 setting has no use       
        set("max_qi", 100); 
        set("max_jing", 100); 
        set("neili", 100); 
        set("max_neili", 100); 
        set("jiali", 100); 
        
        set("combat_exp", 3000000); 
        
        setup(); 
        
        evaluate(init_family[random(sizeof(init_family))]); 
} 
*/

// external functions
public void setup_family(string family);

mapping init_family = ([
        "少林寺"   : (: from_shaolin :),
        "武当派"   : (: from_wudang :),
        "丐帮"     : (: from_gaibang :),
        "华山派"   : (: from_huashan :),
        "雪山寺"   : (: from_xueshan :),
        "桃花岛"   : (: from_taohua :),
        "古墓派"   : (: from_gumu :),
        "全真教"   : (: from_quanzhen :),
        "星宿派"   : (: from_xingxiu :),
        "峨嵋派"   : (: from_emei :),
        "血刀门"   : (: from_xuedao :),
        "逍遥派"   : (: from_xiaoyao :),
        "明教"     : (: from_mingjiao :),
        "灵鹫宫"   : (: from_lingjiu :),
        "神龙教"   : (: from_shenlong :),
        "关外胡家" : (: from_hujia :),
        "欧阳世家" : (: from_ouyang :),
        "慕容世家" : (: from_murong :),
        "段氏皇族" : (: from_duanshi :),
]);


void create()
{
        string *fams;

        NPC_D->generate_cn_name(this_object());
        set("long", "一个人。\n");
        set("gender", "男性");
        set("age", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use      
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);

        set("combat_exp", 3000000);

        setup();

        fams = keys(init_family);
        setup_family(fams[random(sizeof(fams))]);
}

void setup_family(string family)
{
        function f;
        mapping skills;
        string skill;

//      family = FAMILY_D->query_family_name(family);
        if (! functionp(f = init_family[family]))
                return;

        if (mapp(skills = query_skills()))
        {
                // remove all skill
                foreach (skill in keys(skills))
                        delete_skill(skill);

        }

        // set family information
        /*
        set("family/family_name", family);
        set("family/generation", 0);
        */
        create_family(family, 0, "高手"); 

        evaluate(f);
}
        
private void from_wudang()
{
        set("scale", 200);
        set("from", ({
                "据说此人出自武当，是武当派的高手，然而修武不修德，可惜啊可惜。",
                "听闻此人本是武当山下一农夫，耳渎目染，居然练就成非凡武功。",
                "据说此人乃武当弃徒，当年犯了杀戒逃至东洋，不想今日返回中原！",
        }));

        set_skill("force", 1);
        set_skill("taiji-shengong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("tiyunzong", 1);
        set_skill("sword", 1);
        set_skill("taiji-jian", 1);
        set_skill("cuff", 1);
        set_skill("taiji-quan", 1);

        map_skill("parry", "taiji-jian");
        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("sword", "taiji-jian");
        map_skill("cuff", "taiji-quan");

        prepare_skill("cuff", "taiji-quan");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.sui" :),
                (: perform_action, "unarmed.ji" :),
                (: exert_function, "recover" :),
        }) );

        set("class", "taoist");

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}
           
private void from_shaolin()
{
        set("scale", 150);
        set("from", ({
                "据说此人出自少林，是少林的俗家高手，可却没有半点慈悲之心，唉！",
                "听闻此人偷师于少林，练就了一身超凡脱俗的本领。",
                "据说此人乃少林的火工头陀，偷学武艺后被发现，竟然打死"
                + "达摩院长老出逃西域，想不到今日返回中原！",
                "据说此人当年犯了少林的戒律，被迫离寺，想不到隐居多年"
                + "以后居然重出江湖。"
        }));

        set_skill("force", 1);
        set_skill("hunyuan-yiqi", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("shaolin-shenfa", 1);
        set_skill("sword", 1);
        set_skill("damo-jian", 1);
        set_skill("finger", 1);
        set_skill("nianhua-zhi", 1);
        set_skill("strike", 1);
        set_skill("sanhua-zhang", 1);

        map_skill("parry", "damo-jian");
        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("sword", "damo-jian");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sanjue" :),
                (: perform_action, "strike.sanhua" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set("class", "bonze");

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
 
private void from_huashan()
{
        set("scale", 130);
        set("from", ({
                "据说此人出自华山，无恶不作，后来行迹忽然不见，想不到今日又出头。",
                "听闻此人本是华山长老，因剑气之争远投异地，不知何故返回中原！",
                "据说此人本是别派卧底到华山去的，偷学本领以后没回本派"
                + "反而觅地苦修，今日终于得出江湖。",
        }));

        set_skill("force", 1);
        set_skill("zixia-shengong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("huashan-shenfa", 1);
        set_skill("sword", 1);
        set_skill("huashan-sword", 1);

        map_skill("parry", "huashan-sword");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "huashan-shenfa");
        map_skill("sword", "huashan-sword");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jianzhang" :),
                (: perform_action, "sword.wudui" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        set("class", "fighter");

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

private void from_ouyang() 
{ 
        set("scale", 130); 
        set("from", ({ 
                "据说此人原是当今武林宗师欧阳锋的兄长，不知何故失踪，今" 
                + "日居然又出现了。", 
                "听闻此人偷学了西域白驼山庄欧阳世家的武功，后来被欧阳" 
                + "锋发现打成重伤，此人带伤而走，竟然活到今日，不可思议！", 
        })); 
        
        set_skill("force", 1); 
        set_skill("hamagong", 1); 
        set_skill("parry", 1); 
        set_skill("dodge", 1); 
        set_skill("chanchu-bufa", 1); 
        set_skill("staff", 1); 
        set_skill("lingshe-zhangfa", 1); 
        set_skill("cuff", 1); 
        set_skill("lingshe-quan", 1); 
        set_skill("finger", 1); 
        set_skill("shedu-qiqiao", 1); 
        set_skill("literate", 1); 
        set_skill("martial-cognize", 1); 
        
        map_skill("force", "hamagong"); 
        map_skill("parry", "lingshe-zhangfa"); 
        map_skill("dodge", "chanchu-bufa"); 
        map_skill("staff", "lingshe-zhangfa"); 
        map_skill("cuff", "lingshe-quan"); 
        map_skill("finger", "shedu-qiqiao"); 
              
        prepare_skill("cuff", "lingshe-quan"); 
        prepare_skill("finger", "shedu-qiqiao"); 
        
        set("chat_chance_combat", 100); 
        set("chat_msg_combat", ({ 
                (: perform_action, "staff.lingshe" :), 
                (: perform_action, "staff.wyji" :), 
                (: perform_action, "cuff.rou" :), 
                (: exert_function, "powerup" :), 
                (: exert_function, "recover" :), 
        }) ); 
        
        carry_object("/clone/weapon/gangzhang")->wield(); 
        carry_object("/clone/cloth/cloth")->wear(); 
} 
        
private void from_gaibang()
{
        set("scale", 130);
        set("from", ({
                "据说此人原是丐帮长老，武功高绝，后因欺辱良家女子而被"
                + "逐出帮外，今日重现江湖比如又起血雨腥风。"
        }));

        set_skill("force", 1);
        set_skill("huntian-qigong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("xiaoyaoyou", 1);
        set_skill("staff", 1);
        set_skill("dagou-bang", 1);
        set_skill("strike", 1);
        set_skill("dragon-strike", 1);

        map_skill("force", "huntian-qigong");
        map_skill("parry", "dagou-bang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "dragon-strike");

        prepare_skill("strike", "dragon-strike");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
        }) );

        set("class", "begger");

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
         
private void from_taohua()
{
        set("scale", 135);
        set("from", ({
                "据说此人和桃花岛主黄药师有些关系。",
        }));

        set_skill("force", 1);
        set_skill("bibo-shengong", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("luoying-shenfa", 1);
        set_skill("sword", 1);
        set_skill("yuxiao-jianfa", 1);
        set_skill("strike", 1);
        set_skill("luoying-shenzhang", 1);
        set_skill("unarmed", 1);
        set_skill("xuanfeng-tui", 1);
        set_skill("hand", 1);
        set_skill("lanhua-shou", 1);
        set_skill("finger", 1);
        set_skill("tanzhi-shentong", 1);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("strike", "luoying-shenzhang");
        map_skill("hand", "lanhua-shou");
        map_skill("finger", "tanzhi-shentong");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("parry", "yuxiao-jianfa");
        map_skill("sword", "yuxiao-jianfa");

        prepare_skill("strike", "luoying-shenzhang");
        prepare_skill("unarmed", "xuanfeng-tui");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "sword.qing" :),
                (: perform_action, "sword.tianwai" :),
                (: perform_action, "hand.fuxue" :),
                (: perform_action, "finger.jinglei" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
          
private void from_gumu()
{
        object ob;

        set("scale", 130);
        set("from", ({
                "据说此人是林朝英的弟子，被她逐出师门了。",
                "这人据说是古墓传人，和李莫愁颇有渊源。",
        }));

        set_skill("force", 1);
        set_skill("yunv-xinfa", 1);
        set_skill("parry", 1);
        set_skill("dodge", 1);
        set_skill("yunv-shenfa", 1);
        set_skill("unarmed", 1);
        set_skill("meinv-quan", 1);
        set_skill("strike", 1);
        set_skill("fireice-strike", 1);
        set_skill("tianluo-diwang", 1);
        set_skill("throwing", 1);
        set_skill("yufeng-zhen", 1);
        set_skill("sword", 1);
        set_skill("yunv-jian", 1);
        set_skill("quanzhen-jian", 1);

        map_skill("force", "yunv-xinfa");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");
        map_skill("strike", "tianluo-diwang");
        map_skill("throwing", "yufeng-zhen");

        prepare_skill("unarmed", "meinv-quan");
        prepare_skill("strike", "tianluo-diwang");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "strike.wang" :),
                (: perform_action, "sword.he" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "unarmed.you" :),
                (: perform_action, "throwing.wuying" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        ob = carry_object("/d/gumu/obj/yfzhen");
        ob->set_amount(300);
        set_temp("handing", ob);
}

private void from_xingxiu()
{
        set("scale", 130);
        set("from", ({
                "据说此人是星宿派弟子，因为得罪了老仙，只好逃出星宿派。",
        }));

        set_skill("force", 1);
        set_skill("huagong-dafa", 1);
        set_skill("guixi-gong", 1);
        set_skill("throwing", 1);
        set_skill("feixing-shu", 1);
        set_skill("dodge", 1);
        set_skill("zhaixinggong", 1);
        set_skill("strike", 1);
        set_skill("chousui-zhang", 1);
        set_skill("claw", 1);
        set_skill("sanyin-zhua", 1);
        set_skill("whip", 1);
        set_skill("chanhun-suo", 1);
        set_skill("parry", 1);
        set_skill("staff", 1);
        set_skill("poison", 1);
        set_skill("tianshan-zhang", 1);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-zhua");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "staff.fugu" :),
                (: perform_action, "staff.xue" :),
                (: perform_action, "strike.biyan" :),
                (: perform_action, "strike.huolang" :),
                (: perform_action, "strike.huoqiu" :),
                (: perform_action, "strike.huoyan" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

private void from_xueshan()
{
        set("scale", 135);
        set("from", ({
                "据说此人是雪山派的高手，独创中原，横行无忌，武功甚是了得。",
        }));

        set_skill("force", 1);
        set_skill("longxiang-gong", 1);
        set_skill("mizong-neigong", 1);
        set_skill("dodge", 1);
        set_skill("shenkong-xing", 1);
        set_skill("cuff", 1);
        set_skill("yujiamu-quan", 1);
        set_skill("hand", 1);
        set_skill("dashou-yin", 1);
        set_skill("parry", 1);
        set_skill("staff", 1);
        set_skill("xiangmo-chu", 1);
        set_skill("lamaism", 1);
        set_skill("hammer", 1);
        set_skill("riyue-lun", 1);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "riyue-lun");
        map_skill("sword", "xiangmo-chu");
        map_skill("hammer", "riyue-lun");

        prepare_skill("hand", "dashou-yin");
        prepare_skill("cuff", "yujiamu-quan");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.poli" :),
                (: perform_action, "hammer.wulun" :),
                (: perform_action, "hand.jingang" :),
                (: perform_action, "cuff.chen" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("class", "bonze");

        carry_object("/d/xueshan/obj/yinlun")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

private void from_xuedao() 
{ 
        set("scale", 135); 
        set("from", ({ 
                "据说此人和西域血刀老祖是师兄弟，一般的心狠手辣。", 
        })); 
        
        set_skill("force", 1); 
        set_skill("xuehai-mogong", 1); 
        set_skill("blade", 1); 
        set_skill("xuedao-daofa", 1); 
        set_skill("dodge", 1); 
        set_skill("shenkong-xing", 1); 
        set_skill("hand", 1); 
        set_skill("dashou-yin", 1); 
        set_skill("cuff", 1); 
        set_skill("yujiamu-quan", 1); 
        set_skill("parry", 1); 
        set_skill("lamaism", 1); 
        set_skill("literate", 1); 
        set_skill("martial-cognize", 1); 
        
        map_skill("force", "xuehai-mogong"); 
        map_skill("dodge", "shenkong-xing"); 
        map_skill("hand", "dashou-yin"); 
        map_skill("cuff", "yujiamu-quan"); 
        map_skill("parry", "xuedao-daofa"); 
        map_skill("blade", "xuedao-daofa"); 
        map_skill("sword", "mingwang-jian"); 
        
        prepare_skill("cuff", "yujiamu-quan"); 
        prepare_skill("hand", "dashou-yin"); 
        
        set("chat_chance_combat", 80); 
        set("chat_msg_combat", ({ 
                (: perform_action, "blade.ying" :), 
                (: perform_action, "blade.chi" :), 
                (: perform_action, "blade.xue" :), 
                (: perform_action, "blade.shi" :), 
                (: perform_action, "hand.yin" :), 
                (: perform_action, "cuff.jiang" :), 
                (: exert_function, "recover" :), 
                (: exert_function, "resurrect" :), 
                (: exert_function, "powerup" :), 
        })); 
        
        set("class", "bonze"); 
        
        carry_object("/clone/weapon/gangdao")->wield(); 
        carry_object("/clone/misc/cloth")->wear(); 
} 
        
private void from_xiaoyao() 
{ 
        set("scale", 135); 
        set("from", ({ 
                "据说此人和逍遥派无崖子本是同门弟子，后来不知何故翻脸成仇。", 
        })); 
        
        set_skill("force", 1); 
        set_skill("beiming-shengong", 1); 
        set_skill("dodge", 1); 
        set_skill("feiyan-zoubi", 1); 
        set_skill("liuyang-zhang", 1); 
        set_skill("parry", 1); 
        set_skill("sword", 1); 
        set_skill("liuyue-jian", 1); 
        set_skill("zhemei-shou", 1); 
        set_skill("hand", 1); 
        set_skill("strike", 1); 
        set_skill("literate", 1); 
        set_skill("martial-cognize", 1); 
        
        map_skill("force", "beiming-shengong"); 
        map_skill("dodge", "feiyan-zoubi"); 
        map_skill("hand", "zhemei-shou"); 
        map_skill("strike", "liuyang-zhang"); 
        map_skill("parry", "liuyue-jian"); 
        map_skill("sword", "liuyue-jian"); 
        
        prepare_skill("hand","zhemei-shou"); 
        prepare_skill("strike","liuyang-zhang"); 
        
        set("class", "taoist"); 
        
        set("chat_chance_combat", 80); 
        set("chat_msg_combat", ({ 
                (: perform_action, "sword.liu" :), 
                (: perform_action, "sword.sheng" :), 
                (: perform_action, "hand.zhe" :), 
                (: perform_action, "hand.hai" :), 
                (: perform_action, "strike.zhong" :), 
                (: perform_action, "strike.huan" :), 
                (: exert_function, "recover" :), 
                (: exert_function, "shield" :), 
                (: exert_function, "powerup" :), 
        })); 
        
        carry_object("/clone/weapon/changjian")->wield(); 
        carry_object("/clone/misc/cloth")->wear(); 
} 
        
private void from_shenlong() 
{ 
        set("scale", 135); 
        set("from", ({ 
                "据说此人是神龙岛洪教主的亲传弟子，后来判出神龙教，独闯江湖。", 
        })); 
        
        set_skill("force", 1); 
        set_skill("shenlong-xinfa", 1); 
        set_skill("dodge", 1); 
        set_skill("yixingbu", 1); 
        set_skill("hand", 1); 
        set_skill("shenlong-bashi", 1); 
        set_skill("strike", 1); 
        set_skill("huagu-mianzhang", 1); 
        set_skill("parry", 1); 
        set_skill("staff", 1); 
        set_skill("sword", 1); 
        set_skill("shedao-qigong", 1); 
        set_skill("literate", 1); 
        set_skill("martial-cognize", 1); 
        
        map_skill("force", "shenlong-xinfa"); 
        map_skill("dodge", "yixingbu"); 
        map_skill("hand", "shenlong-bashi"); 
        map_skill("strike", "huagu-mianzhang"); 
        map_skill("parry", "shedao-qigong"); 
        map_skill("staff", "shedao-qigong"); 
        
        prepare_skill("strike", "huagu-mianzhang"); 
        prepare_skill("hand", "shenlong-bashi"); 
        
        set("chat_chance_combat", 80); 
        set("chat_msg_combat", ({ 
                (: perform_action, "strike.hua" :), 
                (: perform_action, "hand.xian" :), 
                (: exert_function, "powerup" :), 
                (: exert_function, "recover" :), 
        })); 
        
        carry_object("/clone/misc/cloth")->wear(); 
} 

private void from_lingjiu() 
{  
        set("scale", 130);
        set("from", ({   
                "此人是灵鹫宫的叛徒。现在正在逃亡。", 
        }));

        set_skill("force", 1);
        set_skill("bahuang-gong", 1);
        set_skill("dodge", 1);
        set_skill("yueying-wubu", 1);
        set_skill("strike", 1);
        set_skill("liuyang-zhang", 1);
        set_skill("hand", 1);
        set_skill("zhemei-shou", 1);
        set_skill("sword", 1);
        set_skill("tianyu-qijian", 1);

        map_skill("force", "bahuang-gong"); 
        map_skill("dodge", "yueying-wubu"); 
        map_skill("strike", "liuyang-zhang"); 
        map_skill("hand", "zhemei-shou"); 
        map_skill("sword", "tianyu-qijian"); 
        map_skill("parry", "tianyu-qijian"); 

        prepare_skill("strike", "liuyang-zhang");
        prepare_skill("hand", "zhemei-shou"); 

        set("chat_chance_combat", 80); 
        set("chat_msg_combat", ({  
                (: exert_function, "recover" :),  
                (: exert_function, "powerup" :),  
                (: perform_action, "hand.zhe" :), 
                (: perform_action, "sword.san" :), 
        }));

        carry_object("/clone/weapon/changjian")->wield(); 
        carry_object("/clone/misc/cloth")->wear();
}  

private void from_mingjiao()
{ 
        set("scale", 130);
        set("from", ({  
                "此人是明教的叛徒。",  
        }));

        set_skill("force", 1);
        set_skill("shenghuo-shengong", 1);
        set_skill("dodge", 1);
        set_skill("qingfu-shenfa", 1);
        set_skill("claw", 1);
        set_skill("sougu-yingzhua", 1);
        set_skill("shenghuo-ling", 1);
        set_skill("parry", 1);  
        set_skill("sword", 1);
        set_skill("parry", 1);

        map_skill("parry", "shenghuo-ling"); 
        map_skill("sword", "shenghuo-ling"); 
        map_skill("dodge", "qingfu-shenfa"); 
        map_skill("force", "shenghuo-shengong"); 
        map_skill("claw", "sougu-yingzhua"); 

        prepare_skill("claw", "sougu-yingzhua"); 

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({  
                  (: perform_action, "sword.guanghua" :),  
                  (: perform_action, "claw.xue" :),  
                  (: exert_function, "recover" :), 
        }));

        carry_object("/clone/weapon/changjian")->wield(); 
        carry_object("/clone/misc/cloth")->wear(); 
}

private void from_quanzhen() 
{ 
        set("scale", 150); 
        set("from", ({ 
               "据说此人出自全真，是全真派高手。", 
               "据说此人是王重阳的弟子，被他逐出师门了。", 
        }));

        set_skill("force", 1); 
        set_skill("xiantian-gong", 1); 
        set_skill("jinyan-gong", 1); 
        set_skill("dodge", 1); 
        set_skill("strike", 1); 
        set_skill("finger", 1); 
        set_skill("sword", 1); 
        set_skill("quanzhen-jian", 1); 
        set_skill("haotian-zhang", 1); 
        set_skill("zhongnan-zhi", 1); 
        set_skill("parry", 1); 

        map_skill("force", "xiantian-gong"); 
        map_skill("dodge", "jinyan-gong"); 
        map_skill("strike", "haotian-zhang"); 
        map_skill("finger", "zhongnan-zhi"); 
        map_skill("sword", "quanzhen-jian"); 
        map_skill("parry", "quanzhen-jian"); 

        prepare_skill("finger", "zhongnan-zhi"); 
        prepare_skill("strike", "haotian-zhang"); 

        set("chat_chance_combat", 80); 
        set("chat_msg_combat", ({ 
                (: exert_function, "powerup" :), 
                (: exert_function, "recover" :), 
                (: perform_action, "sword.ding" :), 
                (: perform_action, "sword.chan" :), 
                (: perform_action, "strike.ju" :), 
                (: perform_action, "finger.zhongnan" :), 
        }));

        carry_object("/clone/weapon/changjian")->wield(); 
        carry_object("/clone/misc/cloth")->wear(); 
}

private void from_emei()
{
        object ob;

        set("scale", 130);
        set("from", ({ 
               "据说此人是灭绝师太的弟子，被她逐出师门了。", 
               "这是灭绝师太的弟子，最心狠手辣的弟子。", 
        })); 

       set_skill("force", 1); 
       set_skill("linji-zhuang", 1); 
       set_skill("parry", 1); 
       set_skill("dodge", 1); 
       set_skill("zhutian-bu", 1); 
       set_skill("sword", 1); 
       set_skill("huifeng-jian", 1); 
       set_skill("finger", 1); 
       set_skill("tiangang-zhi", 1); 
       set_skill("strike", 1); 
       set_skill("jinding-zhang", 1); 

       map_skill("force", "linji-zhuang"); 
       map_skill("dodge", "zhutian-bu"); 
       map_skill("sword", "huifeng-jian"); 
       map_skill("parry", "huifeng-jian"); 
       map_skill("finger", "tiangang-zhi"); 
       map_skill("strike", "jinding-zhang"); 

       prepare_skill("strike", "jinding-zhang"); 
       prepare_skill("finger", "tiangang-zhi"); 

       set("chat_chance_combat", 80);
       set("chat_msg_combat", ({ 
                 (: perform_action, "sword.mie" :), 
                 (: perform_action, "finger.lingkong" :), 
                 (: exert_function, "recover" :), 
                 (: exert_function, "powerup" :), 
        })); 

        set("class", "taoism"); 

        carry_object("/clone/weapon/changjian")->wield(); 
        carry_object("/clone/misc/cloth")->wear(); 
} 

private void from_murong() 
{ 
        object ob;

        set("scale", 130);
        set("from", ({  
               "据说此人是慕容派弟子，由于背叛师门，现在正在逃亡。",  
        }));  

        set_skill("force", 1);
        set_skill("shenyuan-gong", 1);
        set_skill("dodge", 1);
        set_skill("beidou-xianzong", 1);
        set_skill("parry", 1);
        set_skill("douzhuan-xingyi", 1);
        set_skill("sword", 1);
        set_skill("murong-jianfa", 1);
        set_skill("cuff", 1);
        set_skill("qixing-quan", 1);
        set_skill("finger", 1);
        set_skill("canhe-zhi", 1);

        map_skill("force", "shenyuan-gong");  
        map_skill("dodge", "beidou-xianzong");  
        //map_skill("parry", "douzhuan-xingyi");  
        map_skill("parry", "murong-jianfa");  
        map_skill("sword", "murong-jianfa");  
        map_skill("cuff", "qixing-quan");  
        map_skill("finger", "canhe-zhi");  

        prepare_skill("cuff", "qixing-quan");
        prepare_skill("finger", "canhe-zhi");

        set("chat_chance_combat", 80);  
        set("chat_msg_combat", ({  
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "sword.qixing" :),  
                (: perform_action, "finger.lian" :),  
        })); 

        carry_object("/clone/weapon/changjian")->wield();  
        carry_object("/clone/misc/cloth")->wear();  
}

private void from_hujia()
{  
        object ob; 

       set("scale", 130); 
       set("from", ({   
              "据说此人是胡家弟子，背叛师门，逃亡中。",   
       }));

       set_skill("force", 1); 
       set_skill("lengyue-shengong", 1); 
       set_skill("dodge", 1); 
       set_skill("sixiang-bufa", 1); 
       set_skill("cuff", 1); 
       set_skill("hujia-quan", 1); 
       set_skill("strike", 1); 
       set_skill("tianchang-zhang", 1); 
       set_skill("blade", 1); 
       set_skill("hujia-daofa", 1); 
       set_skill("parry", 1); 

       map_skill("force", "lengyue-shengong");   
       map_skill("dodge", "sixiang-bufa");   
       map_skill("cuff", "hujia-quan");   
       map_skill("strike", "tianchang-zhang");   
       map_skill("blade", "hujia-daofa");   
       map_skill("parry", "hujia-daofa");   

       prepare_skill("cuff", "hujia-quan"); 
       prepare_skill("strike", "tianchang-zhang"); 

       set("chat_chance_combat", 80);  
       set("chat_msg_combat", ({   
               (: perform_action, "blade.bafang" :),  
               (: perform_action, "cuff.kuai" :),  
               (: exert_function, "recover" :),  
               (: exert_function, "powerup" :),  
       }));

       carry_object("/clone/weapon/gangdao")->wield();  
       carry_object("/clone/misc/cloth")->wear();   
} 

private void from_duanshi()
{
        set("scale", 135); 
        set("from", ({ 
               "据说此人和段家有些关系。", 
        }));

        set_skill("force", 1); 
        set_skill("kurong-changong", 1); 
        set_skill("sword", 1); 
        set_skill("duanjia-jian", 1); 
        set_skill("parry", 1); 
        set_skill("dodge", 1); 
        set_skill("cuff", 1); 
        set_skill("tiannan-bu", 1); 
        set_skill("jinyu-quan", 1); 
        set_skill("strike", 1); 
        set_skill("wuluo-zhang", 1); 
        set_skill("sun-finger", 1); 
        set_skill("finger", 1); 

        map_skill("force", "kurong-changong");    
        map_skill("sword", "duanjian-jian");    
        map_skill("cuff", "jinyu-quan");    
        map_skill("strike", "wuluo-zhang");    
        map_skill("finger", "sun-finger");    
        map_skill("dodge", "tiannan-bu");    
        map_skill("parry", "duanjian-jian");    

        prepare_skill("finger", "sun-finger");     

        set("chat_chance_combat", 80); 
        set("chat_msg_combat", ({   
                (: exert_function, "powerup" :), 
                (: exert_function, "recover" :), 
                (: perform_action, "sword.jing" :), 
                (: perform_action, "finger.qiankun" :), 
        }));

        carry_object("/clone/weapon/changjian")->wield(); 
        carry_object("/clone/misc/cloth")->wear();   
} 


