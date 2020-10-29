// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是亮相太难的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lxt");
        set("owner_name", "亮相太难");
        set_temp("owner", "lxt");
        set_temp("owner_name", "亮相太难");
        ::setup();
}
