// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m通天炫舞[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "通天炫舞[2;37;0m
它是叶孤城的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "happy");
        set("owner_name", "叶孤城");
        set_temp("owner", "happy");
        set_temp("owner_name", "叶孤城");
        ::setup();
}
