// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤兔马[2;37;0m[2;37;0m", ({"duanyunride"}));        
        set("gender", "男性");                
        set("long", "这是一匹千年难得一遇的宝马[2;37;0m
它是段云的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "duanyun");
        set("owner_name", "段云");
        set_temp("owner", "duanyun");
        set_temp("owner_name", "段云");
        ::setup();
}
