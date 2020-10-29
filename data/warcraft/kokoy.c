// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("皮卡车[2;37;0m[2;37;0m", ({"daibu"}));        
        set("gender", "男性");                
        set("long", "极品皮卡[2;37;0m
它是风飘扬的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "kokoy");
        set("owner_name", "风飘扬");
        set_temp("owner", "kokoy");
        set_temp("owner_name", "风飘扬");
        ::setup();
}
