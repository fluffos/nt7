#include <ansi.h>
inherit NPC;
void create()
{
        set_name("钱二败", ({ "qian erbai","qian","erbai"}) );
        set("long",@LONG
那人看来不算老，却脸皮都皱了起来，身材矮小，原本应是个毫不起眼的汉子，
可是他一对眼睛神芒闪烁，锐利至像能透视别人肺腑般，一脚踏在凳上，手肘枕在膝
头处托着箭壶，有种稳如泰山的感觉，在在都使人感到他绝非平凡之辈。
LONG
         );
        set("title",BLU"神箭八雄"NOR);
        set("nickname","穿云箭");
        set("max_jing", 6000);
        set("max_qi", 6000);                    
        set("max_sen", 6000);
        set("max_neili",6000); 
        set("neili",6000);
        set("jiali",120);     
        set("combat_exp",5800000);
        set("cor",200);
        set("kar",200);
        set("age",65);
        set_skill("pixie-jian", 420);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("sword",420);
        set_skill("force",800); //防止别人来弹指
        set_skill("hamagong",500);
        set_skill("tiyunzong",500);
        map_skill("sword","pixie-jian");
        map_skill("parry","pixie-jian");
        map_skill("dodge","tiyunzong");
        map_skill("force","hamagong");
        set_temp("apply/attack",50);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player())) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
         if(random(15) < 2)
                this_object()->set_leader(ob);
        }
}
