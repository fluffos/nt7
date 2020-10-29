#include <ansi.h>

#define YUXIAO    "/clone/lonely/yuxiao"
#define TAOHUA    "/clone/lonely/book/taohua"
#define XIAOPU    "/clone/lonely/book/xiaopu"
#define XUANFENG  "/clone/lonely/book/xuanfengtui"

inherit NPC;

void create()
{
        object ob;
        set_name("黄药师", ({"huang yaoshi", "huang", "yaoshi"}));
        set("title", "东海桃花岛岛主");
        set("nickname", HIC "东邪" NOR );
        set("gender", "男性");
        set("age", 42);
        set("long", "他就是桃花岛主。行事好恶全由己心，因此被\n"
                    "人称作「东邪」。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("jing", 200000);
        set("qi", 200000);
        set("max_qi", 200000);

        set("max_jing", 200000);
        set("neili", 70000);
        set("max_neili", 70000);
        set("jiali", 200);
        set("combat_exp", 40000000);

        set_skill("force", 550);
        set_skill("bibo-shengong", 540);
        set_skill("luoying-xinfa", 520);
        set_skill("hand", 520);
        set_skill("finger", 540);
        set_skill("canglang-zhi", 520);
        set_skill("tanzhi-shentong", 540);
        set_skill("unarmed", 520);
        set_skill("strike", 520);
        set_skill("pikong-zhang", 520);
        set_skill("luoying-shenzhang", 520);
        set_skill("xuanfeng-tui", 550);
        set_skill("dodge", 520);
        set_skill("anying-fuxiang", 520);
        set_skill("parry", 520);
        set_skill("sword", 520);
        set_skill("throwing", 540);
        set_skill("luoying-shenjian", 520);
        set_skill("yuxiao-jianfa", 520);
        set_skill("lanhua-shou", 520);
        set_skill("qimen-wuxing", 550);
        set_skill("count", 550);
        set_skill("jingluo-xue", 550);
        set_skill("mathematics", 550);
        set_skill("literate", 550);
        set_skill("chuixiao-jifa", 550);
        set_skill("bihai-chaosheng", 550);
        set_skill("taohua-yuan", 550);
        set_skill("drawing", 550);
        set_skill("chess", 550);
        set_skill("calligraphy", 550);
        set_skill("medical", 550);
        set_skill("taohua-yaoli", 550);
        set_skill("martial-cognize", 520);
        set_skill("qimen-xuanshu", 500);

        map_skill("force", "bibo-shengong");
        map_skill("finger", "tanzhi-shentong");
        map_skill("hand", "lanhua-shou");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("dodge", "anying-fuxiang");
        map_skill("parry", "tanzhi-shentong");
        map_skill("sword", "yuxiao-jianfa");
        map_skill("chuixiao-jifa", "bihai-chaosheng");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("medical", "taohua-yaoli");

        prepare_skill("finger" , "tanzhi-shentong");

        create_family("桃花岛", 1, "岛主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.bihai" :),
                (: perform_action, "sword.qing" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "finger.ding" :),
                (: perform_action, "finger.xiao" :),
                (: perform_action, "finger.po" :),
                (: perform_action, "finger.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));
        set_temp("apply/damage", 300);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();

        if (clonep())
        {
                ob = find_object(YUXIAO);
                if (! ob) ob = load_object(YUXIAO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        set_temp("handing", ob);
                } else
                {
                        set_temp("handing", carry_object("/d/taohua/obj/huaban"));
                }
        }
        carry_object("/d/taohua/obj/bupao")->wear();
}
void unconcious()
{
        die();
}   
