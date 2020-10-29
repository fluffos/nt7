// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping knowledge_obj = ([
        "/d/xueshan/obj/fojing2":36,                  //雪山塔底
        "/d/xiaoyao/obj/lbook4":1,                    //暂时无处获取
        "/d/xiaoyao/npc/obj/lbook4":1,                //暂时无处获取
        "/d/shaolin/obj/fojing21":30,                 //少林藏经楼
        "/d/shaolin/obj/fojing20":30,                 //少林藏经楼
        "/d/shaolin/obj/fojing11":30,                 //少林藏经楼
        "/d/shaolin/obj/fojing10":30,                 //少林藏经楼
        "/d/quanzhen/npc/obj/daodejing-ii":30,        //掌理道长、祁志诚
        "/d/quanzhen/npc/obj/daodejing-i":33,         //掌经道长
        "/d/emei/obj/fojing21":28,                    //峨嵋藏经阁、峨嵋藏经楼
        "/d/emei/obj/fojing20":28,                    //峨嵋藏经阁、峨嵋藏经楼
        "/d/emei/obj/fojing11":28,                    //峨嵋藏经阁、峨嵋藏经楼
        "/d/emei/obj/fojing10":28,                    //峨嵋藏经阁、峨嵋藏经楼
        "/d/emei/obj/fojing":33,                      //灭绝师太
        "/d/city/npc/obj/lbook3":1,                   //暂时无处获取
        "/d/changan/npc/obj/book":40,                 //萧员外
        "/clone/book/zhengpu":36,                     //欧阳峰
        "/clone/book/yljing2":1,                      //暂时无处获取
        "/clone/book/yljing1":1,                      //暂时无处获取
        "/clone/book/yljing":1,                       //暂时无处获取
        "/clone/book/yijing3":30,                     //桃花岛书房
        "/clone/book/yijing2":30,                     //桃花岛书房
        "/clone/book/yijing1":30,                     //桃花岛书房
        "/clone/book/yijing0":30,                     //桃花岛书房
        "/clone/book/xiaopu":36,                      //黄药师
        "/clone/book/taohua":36,                      //黄药师
        "/clone/book/qin":36,                         //令狐冲
        "/clone/book/mizong_book":33,                 //雪山藏经室
        "/clone/book/lbook4":33,                      //苟读
        "/clone/book/lbook3":18,                      //朱熹购买
        "/clone/book/lbook2":10,                      //朱熹购买
        "/clone/book/lbook1":7,                       //朱熹购买
        "/clone/book/laozi8":28,                      //武当藏经阁、全真藏经阁
        "/clone/book/laozi2":28,                      //武当藏经阁、全真藏经阁
        "/clone/book/laozi18":28,                     //武当藏经阁、全真藏经阁
        "/clone/book/laozi16":28,                     //武当藏经阁、全真藏经阁
        "/clone/book/laozi13":28,                     //武当藏经阁、全真藏经阁
        "/clone/book/laozi1":28,                      //武当藏经阁、全真藏经阁
        "/clone/book/daodejing":1,                    //暂时无处获取
        "/clone/book/daodejing-ii":33,                //清虚道长
        "/clone/book/daodejing-i":26,                 //谷虚道长、武当藏经阁、全真藏经阁
        "/clone/book/book-paper":26,                  //神龙小屋、燕子钨还施水阁、苟读
        "/clone/book/bagua1":30,                      //桃花岛书房
        "/clone/book/bagua0":30,                      //桃花岛书房
]);

int check_value(string filename)
{
        if (undefinedp(knowledge_obj[filename])) return 0;
        return knowledge_obj[filename];
}
