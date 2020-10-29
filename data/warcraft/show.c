// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"mjt"}));        
        set("gender", "男性");                
        set("long", "可爱的朱雀[2;37;0m
它是晓菲姬的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "show");
        set("owner_name", "晓菲姬");
        set_temp("owner", "show");
        set_temp("owner_name", "晓菲姬");
        ::setup();
}
