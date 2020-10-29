// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("米饭班主[2;37;0m[2;37;0m", ({"mfb"}));        
        set("gender", "男性");                
        set("long", "米饭班主[2;37;0m
它是红米饭的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mifanb");
        set("owner_name", "红米饭");
        set_temp("owner", "mifanb");
        set_temp("owner_name", "红米饭");
        ::setup();
}
