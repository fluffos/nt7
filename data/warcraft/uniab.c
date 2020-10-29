// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸟[2;37;0m[2;37;0m", ({"tutu"}));        
        set("gender", "女性");                
        set("long", "这是一只可爱的小鸟[2;37;0m
它是叶一二的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "uniab");
        set("owner_name", "叶一二");
        set_temp("owner", "uniab");
        set_temp("owner_name", "叶一二");
        ::setup();
}
