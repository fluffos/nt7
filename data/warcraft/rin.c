// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m英灵[2;37;0m[2;37;0m", ({"archer"}));        
        set("gender", "女性");                
        set("long", "这是一个披着红色外衣的英灵，面貌隐隐约约看不大清楚[2;37;0m
它是远坂凛的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "rin");
        set("owner_name", "远坂凛");
        set_temp("owner", "rin");
        set_temp("owner_name", "远坂凛");
        ::setup();
}
