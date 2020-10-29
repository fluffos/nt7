// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("傅立叶[2;37;0m[2;37;0m", ({"fft"}));        
        set("gender", "女性");                
        set("long", "一只朱雀[2;37;0m
它是莉娜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lena");
        set("owner_name", "莉娜");
        set_temp("owner", "lena");
        set_temp("owner_name", "莉娜");
        ::setup();
}
