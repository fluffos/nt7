// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m五[1;36m彩[1;35m凤[1;31m凰[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "女性");                
        set("long", "好漂亮的凤凰，周身萦绕着一道道霞光[2;37;0m
它是心明的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "redheart");
        set("owner_name", "心明");
        set_temp("owner", "redheart");
        set_temp("owner_name", "心明");
        ::setup();
}
