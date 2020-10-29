// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "member zhuan 3 to ian[2;37;0m
它是小泽圆的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ntbu");
        set("owner_name", "小泽圆");
        set_temp("owner", "ntbu");
        set_temp("owner_name", "小泽圆");
        ::setup();
}
