// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[34m蓝鸟[2;37;0m[2;37;0m", ({"redbird"}));        
        set("gender", "女性");                
        set("long", "蓝鸟[2;37;0m
它是乐蓝的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "honor");
        set("owner_name", "乐蓝");
        set_temp("owner", "honor");
        set_temp("owner_name", "乐蓝");
        ::setup();
}
