// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大叫驴[2;37;0m[2;37;0m", ({"donkey"}));        
        set("gender", "男性");                
        set("long", "大叫驴[2;37;0m
它是完颜宗弼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wanyan");
        set("owner_name", "完颜宗弼");
        set_temp("owner", "wanyan");
        set_temp("owner_name", "完颜宗弼");
        ::setup();
}
