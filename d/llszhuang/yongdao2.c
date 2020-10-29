inherit ROOM;
void create()
{
       set("short", "柳绿山庄");
        set("long",
"渐行渐远，你只觉自己脚下格格作响，似是踢到了什么东西，又似踩\n"
"碎了什么东西。你定神一看，原来一地都是白骨，更有些人似乎死去不久，\n"
"全身没有丝毫血色，全身腐烂了个七七八八，身边全是兵器看来都是武林\n"
"中人。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "northwest" : __DIR__"yongdao3",
          "south" : __DIR__"yongdao1",
        ]));

        setup();
}
