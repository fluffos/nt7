// gzf 鬼丈夫

#include <ansi.h>;
inherit NPC;

void create()
{
        set_name(HIW "渴口" NOR, ({ "coke" }));
        set("title", HIR "幸运之神" NOR);
        set("gender", "男性");
        set("age", 35);
        set("no_get", 1);
        set("long", @LONG
　　　　此人:
　　　　字迹工整， 
　　　　文笔极佳， 
　　　　才思敏捷， 
　　　　过目不忘， 
　　　　十年寒窗， 
　　　　博学多才， 
　　　　见多识广， 
　　　　才高八斗， 
　　　　日理万机， 
　　　　明察秋毫， 
　　　　英明果断， 
　　　　分身有术， 
　　　　孜孜不倦， 
　　　　吾等楷模 在下对你的景仰之情有如滔滔长江之水， 
　　　　连绵不绝 
　　　　…… 
　　　　又如黄河泛滥， 
　　　　一发不可收拾 
　　　　…… 
　　　　嘿嘿 
　　　　惊天地！ 
　　　　泣鬼神！ 
　　　　感人肺腑！ 
　　　　感人落泪！ 
　　　　i 服了 u！ 

他是泥潭系列有装备系统从nt3开始到nt7第一个洗出太古的玩家，鸿运当头，运气极佳！
LONG );
        set("combat_exp", 60000);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("apply/attack", 50);
        set("apply/defense", 50);

        set("max_qi", 800);
        set("max_jing", 800);
        set("max_neili", 800);

        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
