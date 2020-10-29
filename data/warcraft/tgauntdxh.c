// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是令狐妹泰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tgauntdxh");
        set("owner_name", "令狐妹泰");
        set_temp("owner", "tgauntdxh");
        set_temp("owner_name", "令狐妹泰");
        ::setup();
}
