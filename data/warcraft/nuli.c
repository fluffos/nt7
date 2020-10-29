// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "女性");                
        set("long", "在天的见证之下，集勇气、智慧、与美丽于一身的强大生物![2;37;0m
它是三吻鱼的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "nuli");
        set("owner_name", "三吻鱼");
        set_temp("owner", "nuli");
        set_temp("owner_name", "三吻鱼");
        ::setup();
}
