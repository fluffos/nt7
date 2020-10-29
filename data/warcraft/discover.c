// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m混沌[2;37;0m[2;37;0m", ({"chaos"}));        
        set("gender", "男性");                
        set("long", "有目而不见,有耳而不闻,人有德行而往抵触之,有凶德则往依凭之![2;37;0m
它是一生何求的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "discover");
        set("owner_name", "一生何求");
        set_temp("owner", "discover");
        set_temp("owner_name", "一生何求");
        ::setup();
}
