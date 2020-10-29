// huoji. 

inherit NPC;
#include <ansi.h>
inherit F_DEALER;

void create()
{
        set_name("情儿", ({ "qing er", "qing" }));
        set("title", HIM"琴瑟和鸣"NOR);
        set("nickname",HIR"赤绳绾结"NOR);
        set("shen_type", 1);

        set("str", 30);
        set("gender", "女性");
        set("age", 17);
         set("per", 30);
        set("long",
"一个常驻月老祠附近的小姑娘，卖一些稀
罕的东西，悬奇古怪，据说有助姻缘。\n"
);
        set("combat_exp", 2500);
        set("attitude", "friendly");
        set("chat_chance", 1);
        set("chat_msg", ({
                "情儿笑眯眯地说道：“求姻缘啊？来看看我卖的东西吧！”\n",
        }));

        set("vendor_goods", ({
                "/d/hangzhou/npc/obj/yuelao-xianshui.c",
                "/d/hangzhou/npc/obj/sansheng-youyue.c",
                "/d/hangzhou/npc/obj/ruyi-su.c",
                "/d/hangzhou/npc/obj/tongxin-jie.c",
                "/d/hangzhou/npc/obj/xuannv-lingfu.c",
                "/d/hangzhou/npc/obj/huangtong-suo.c",
        }));

        setup();
        carry_object("/d/hangzhou/npc/obj/sahua-qun.c")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
