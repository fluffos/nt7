// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping blade_obj = ([
        "/d/xueshan/obj/xblade1":1,             //暂时无处获取
        "/d/xueshan/obj/xblade":30,             //血刀老祖、红日尊者
        "/d/xiaoyao/obj/blade":25,              //逍遥打铁屋
        "/d/xiaoyao/npc/obj/blade":30,          //逍遥蒙面人
        "/d/xiangyang/npc/obj/mudao":5,         //木匠购买
        "/d/xiakedao/obj/knife":5,              //侠客岛的一律廉价
        "/d/xiakedao/obj/gangdao":5,            //侠客岛的一律廉价
        "/d/shaolin/obj/mudao":25,              //少林武器库
        "/d/shaolin/obj/jiedao":10,             //很多
        "/d/quanzhou/npc/obj/wodao":24,         //倭寇（六个）
        "/d/quanzhen/npc/obj/gangdao":18,       //全真禅房、武功镇官兵（四个）
        "/d/mingjiao/obj/jiedao":1,             //暂时无处获取
        "/d/mingjiao/obj/gangdao":1,            //暂时无处获取
        "/d/heimuya/npc/obj/dadao":25,          //贾布、黄伯流、上官云、童百熊
        "/d/guiyun/npc/obj/jiandao":36,         //张阿生
        "/d/guanwai/obj/lengyue":36,            //胡斐
        "/d/guanwai/obj/cwbdao":40,             //胡斐
        "/d/foshan/npc/obj/caidao":36,          //钟四嫂
        "/d/dali/npc/obj/mandao":36,            //傣族首领
        "/d/dali/npc/obj/kandao":26,            //采笋人（两个）、砍竹人（两个）
        "/d/city/obj/gangdao":5,                //很多
        "/d/city/npc/obj/gangdao":5,            //很多
        "/d/changan/npc/obj/gangdao":5,         //很多
        "/d/changan/npc/obj/blade":5,           //很多
        "/d/beijing/npc/obj/blade3":10,         //北京官兵（相当多）
        "/d/beijing/npc/obj/blade2":5,          //江湖豪客（四个）、毒郎中（无数）、李力世
        "/d/beijing/npc/obj/blade1":5,          //很多
        "/d/baituo/obj/dadao":18,               //白驼山五个门卫、三个山贼、一个山贼头
        "/d/baituo/obj/chaidao":30,             //樵夫、老材
        "/d/baituo/npc/obj/dadao":1,            //暂时无处获取
        "/d/baituo/npc/obj/chaidao":1,          //暂时无处获取
        "/clone/weapon/wandao":7,               //可以购买:12两白银
        "/clone/weapon/tudao":8,                //可以购买:20两白银
        "/clone/weapon/mudao":5,                //很多
        "/clone/weapon/jpn-dao":10,             //日本外敌
        "/clone/weapon/jiedao":1,               //暂时无处获取
        "/clone/weapon/gangdao":5,              //很多
        "/clone/weapon/dadao":36,               //马超兴
        "/clone/weapon/blade":5,                //很多
]);

int check_value(string filename)
{
        if (undefinedp(blade_obj[filename])) return 0;
        return blade_obj[filename];
}
