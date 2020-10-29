// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猪[2;37;0m[2;37;0m", ({"zzq"}));        
        set("gender", "男性");                
        set("long", "小猪[2;37;0m
它是牛小一的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wdlowek");
        set("owner_name", "牛小一");
        set_temp("owner", "wdlowek");
        set_temp("owner_name", "牛小一");
        ::setup();
}
