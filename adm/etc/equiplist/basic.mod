#modlist

<M0000>
<name>$WHT$文曲星学习套装(凡)</name>
<file>
A0000
A0001
A0002
A0003
A0004
A0005
A0006
</file>
<stats>
int:180
study_effect:180
learn_effect:180
research_effect:180
practice_effect:180
derive_effect:180
</stats>
</M0000>

<M0001>
<name>$WHT$战神套装(凡)</name>
<file>
A1010
A1011
A1012
A1013
A1014
A1015
</file>
<stats>
max_neili:30000
max_jingli:10000
max_qi:5000
max_jing:3000
</stats>
</M0001>

<M0002>
<name>$WHT$盘古套装(凡)</name>
<file>
A1020
A1021
A1022
A1023
A1024
A1025
</file>
<stats>
max_neili:30000
max_jingli:10000
max_qi:5000
max_jing:3000
</stats>
</M0001>


#eqlist

<A0000>
<type>armor/armor</type>
<name>$WHT$文曲星甲</name>
<id>wisdom armor</id>
<long>蕴含了文曲星的精元和无上智慧(凡)。</long>
<value>10000000</value>
<mod>M0000</mod>
<enchase>
apply_prop/armor:300
apply_prop/study_effect:5
apply_prop/practice_effect:5
apply_prop/int:3
</enchase>
</A0000>

<A0001>
<type>armor/surcoat</type>
<name>$WHT$文曲星披风</name>
<id>wisdom surcoat</id>
<long>蕴含了文曲星的精元和无上智慧(凡)。</long>
<value>10000000</value>
<mod>M0000</mod>
<enchase>
apply_prop/armor:100
apply_prop/study_effect:5
apply_prop/derive_effect:5
apply_prop/int:3
</enchase>
</A0001>

<A0002>
<type>armor/wrists</type>
<name>$WHT$文曲星护腕</name>
<id>wisdom wrists</id>
<long>蕴含了文曲星的精元和无上智慧(凡)。</long>
<value>10000000</value>
<mod>M0000</mod>
<enchase>
apply_prop/armor:100
apply_prop/study_effect:5
apply_prop/practice_effect:5
apply_prop/int:3
</enchase>
</A0002>

<A0003>
<type>armor/waist</type>
<name>$WHT$文曲星束带</name>
<id>wisdom waist</id>
<long>蕴含了文曲星的精元和无上智慧(凡)。</long>
<value>10000000</value>
<mod>M0000</mod>
<enchase>
apply_prop/armor:100
apply_prop/learn_effect:5
apply_prop/derive_effect:5
apply_prop/int:3
</enchase>
</A0003>

<A0004>
<type>armor/head</type>
<name>$WHT$文曲星头盔</name>
<id>wisdom head</id>
<long>蕴含了文曲星的精元和无上智慧(凡)。</long>
<value>10000000</value>
<mod>M0000</mod>
<enchase>
apply_prop/armor:100
apply_prop/learn_effect:5
apply_prop/research_effect:5
apply_prop/int:3
</enchase>
</A0004>

<A0005>
<type>armor/boots</type>
<name>$WHT$文曲星靴</name>
<id>wisdom boots</id>
<long>蕴含了文曲星的精元和无上智慧(凡)。</long>
<value>10000000</value>
<mod>M0000</mod>
<enchase>
apply_prop/armor:100
apply_prop/learn_effect:5
apply_prop/practice_effect:5
apply_prop/int:3
</enchase>
</A0005>

<A0006> 
<type>armor/cloth</type> 
<name>$WHT$文曲星战衣$NOR$</name> 
<id>wisdom cloth</id> 
<long>一件丝质的衣服。</long> 
<value>20000</value> 
<mod_level>M0000</mod_level> 
<long>蕴含了文曲星的精元和无上智慧(凡)。</long>
<armor_prop> 
armor:20
</armor_prop> 
<enchase> 
apply_prop/armor1:20 
apply_prop/study_effect:10 
apply_prop/practice_effect:10 
apply_prop/int:8 
flute:2
used:2
</enchase> 
<insert> 
[1] 
id:magic stone 
name:$HIM$玄石$NOR$ 
apply_prop/armor1:30
apply_prop/int:8
[/1]
[2]
id:magic stone
name:$HIM$玄石$NOR$
apply_prop/research_effect:10
apply_prop/derive_effect:10
[/2] 
</insert> 
</A0006> 
