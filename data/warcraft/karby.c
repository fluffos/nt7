// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m脆笛酥[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "$HIM$脆笛酥[2;37;0m
它是小瓜呆的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "karby");
        set("owner_name", "小瓜呆");
        set_temp("owner", "karby");
        set_temp("owner_name", "小瓜呆");
        ::setup();
}
