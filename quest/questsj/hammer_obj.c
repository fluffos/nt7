// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping hammer_obj = ([
        "/d/xueshan/obj/yinlun":1,            //暂时无处获取
        "/d/xueshan/obj/lubo":36,             //莲座
        "/d/xueshan/obj/jinlun":1,            //暂时无处获取
        "/d/xueshan/obj/falun":20,            //雪山库房、随机三个之内
        "/d/xueshan/obj/faling":18,           //祭祀喇嘛(四个)、塔底
        "/d/xingxiu/obj/yaochu":26,           //神农弟子、采药人（三个）
        "/d/xiakedao/obj/zhutou":1,           //侠客岛的一律廉价
        "/d/xiakedao/obj/forleg":1,           //侠客岛的一律廉价
        "/d/xiakedao/obj/backleg":1,          //侠客岛的一律廉价
        "/d/xiakedao/npc/obj/jitui":1,        //侠客岛的一律廉价
        "/d/wudang/obj/shitou":20,            //武当小路
        "/d/wanjiegu/npc/obj/muyu":34,        //黄眉大师
        "/d/village/npc/obj/hothammer":33,    //冯铁匠
        "/d/village/npc/obj/hammer":5,        //冯铁匠购买
        "/d/tulong/yitian/npc/obj/tongbo":18, //钵僧
        "/d/tulong/tulong/obj/stone":5,       //海滩
        "/d/tulong/tulong/npc/obj/hammer":36, //常金鹏
        "/d/shaolin/obj/muchui":25,           //少林东侧殿、西侧殿
        "/d/quanzhen/npc/obj/jitui":5,        //购买
        "/d/mingjiao/obj/shigu":22,           //戈壁滩（六根）
        "/d/mingjiao/obj/mutang":22,          //山门门卫（两个）、巫士四个
        "/d/heimuya/obj/zijinchui":1,         //暂时无处获取
        "/d/heimuya/npc/obj/zijinchui":33,    //童百熊
        "/d/hangzhou/obj/shitou":20,          //杭州宝石山
        "/d/guanwai/npc/obj/tongren":33,      //滕一雷
        "/d/guanwai/npc/obj/tiepipa":33,      //焦文期
        "/d/foshan/obj/shikuai":12,           //佛山林间道
        "/d/dali/npc/obj/yaoqin":30,          //大理歌女（两个）
        "/d/chengdu/npc/obj/jitui":5,           //可以购买
        "/d/city/obj/stone":20,               //蛇谷
        "/d/city/obj/shitou":15,              //扬州城外密林
        "/d/city/obj/jitui":5,                //可以购买
        "/d/city/obj/hammer":1,               //暂时无处获取
        "/d/city/obj/bone":26,                //大和街边
        "/d/city/npc/obj/jitui":5,            //可以购买
        "/d/city/npc/obj/hammer":1,           //暂时无处获取
        "/d/changan/npc/obj/jitui":5,         //可以购买
        "/d/changan/npc/obj/hammer":26,       //慕容豪、张衡、萧群
        "/d/beijing/npc/obj/hammer":25,       //北京铁匠
        "/clone/weapon/hammer":5,             //很多
        "/clone/weapon/falun":5,              //很多
        "/clone/food/jitui":5,                //可以购买
]);

int check_value(string filename)
{
        if (undefinedp(hammer_obj[filename])) return 0;
        return hammer_obj[filename];
}
