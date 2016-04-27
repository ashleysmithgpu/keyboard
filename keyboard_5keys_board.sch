<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.1.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="5" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="cherrymx">
<description>Cherry MX Keyswitch PCB footprints</description>
<packages>
<package name="CHERRY-MX">
<description>Cherry MX Keyswitch footprint</description>
<wire x1="-7.62" y1="7.62" x2="7.62" y2="7.62" width="0.127" layer="21"/>
<wire x1="7.62" y1="7.62" x2="7.62" y2="-7.62" width="0.127" layer="21"/>
<wire x1="7.62" y1="-7.62" x2="-7.62" y2="-7.62" width="0.127" layer="21"/>
<wire x1="-7.62" y1="-7.62" x2="-7.62" y2="7.62" width="0.127" layer="21"/>
<pad name="SW1" x="-3.81" y="2.54" drill="1.5" diameter="2.54"/>
<pad name="SW2" x="2.54" y="5.08" drill="1.5" diameter="2.54"/>
<pad name="P$3" x="-5.08" y="0" drill="1.7144" diameter="1.9304"/>
<pad name="P$4" x="5.08" y="0" drill="1.7144" diameter="1.9304"/>
<hole x="0" y="0" drill="4.0004"/>
</package>
</packages>
<symbols>
<symbol name="CHERRY-MX">
<description>Basic part for Cherry MX series keyswitch</description>
<text x="-6.096" y="5.842" size="1.4224" layer="95">CHERRY-MX</text>
<pin name="PIN-1" x="-10.16" y="2.54" length="middle"/>
<pin name="PIN-2" x="-10.16" y="-2.54" length="middle"/>
<text x="-5.08" y="-7.62" size="1.778" layer="95">&gt;NAME</text>
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CHERRY-MX">
<description>Cherry MX series keyswitch</description>
<gates>
<gate name="G$1" symbol="CHERRY-MX" x="-2.54" y="-25.4"/>
</gates>
<devices>
<device name="" package="CHERRY-MX">
<connects>
<connect gate="G$1" pin="PIN-1" pad="SW1"/>
<connect gate="G$1" pin="PIN-2" pad="SW2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diode">
<description>&lt;b&gt;Diodes&lt;/b&gt;&lt;p&gt;
Based on the following sources:
&lt;ul&gt;
&lt;li&gt;Motorola : www.onsemi.com
&lt;li&gt;Fairchild : www.fairchildsemi.com
&lt;li&gt;Philips : www.semiconductors.com
&lt;li&gt;Vishay : www.vishay.de
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DO35-10">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 2 mm, horizontal, grid 10.16 mm</description>
<wire x1="5.08" y1="0" x2="4.191" y2="0" width="0.508" layer="51"/>
<wire x1="-5.08" y1="0" x2="-4.191" y2="0" width="0.508" layer="51"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.635" x2="1.016" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.016" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.032" y1="1.016" x2="2.286" y2="0.762" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.286" y1="0.762" x2="-2.032" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.286" y1="-0.762" x2="-2.032" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="2.032" y1="-1.016" x2="2.286" y2="-0.762" width="0.1524" layer="21" curve="90"/>
<wire x1="2.286" y1="-0.762" x2="2.286" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="0.762" x2="-2.286" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="1.016" x2="2.032" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="-1.016" x2="2.032" y2="-1.016" width="0.1524" layer="21"/>
<pad name="C" x="-5.08" y="0" drill="0.8128" shape="long"/>
<pad name="A" x="5.08" y="0" drill="0.8128" shape="long"/>
<text x="-2.159" y="1.27" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.159" y="-2.667" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-1.905" y1="-1.016" x2="-1.397" y2="1.016" layer="21"/>
<rectangle x1="2.286" y1="-0.254" x2="4.191" y2="0.254" layer="21"/>
<rectangle x1="-4.191" y1="-0.254" x2="-2.286" y2="0.254" layer="21"/>
</package>
<package name="DO35-7">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 2 mm, horizontal, grid 7.62 mm</description>
<wire x1="3.81" y1="0" x2="2.921" y2="0" width="0.508" layer="51"/>
<wire x1="-3.81" y1="0" x2="-2.921" y2="0" width="0.508" layer="51"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.635" x2="1.016" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.016" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.032" y1="1.016" x2="2.286" y2="0.762" width="0.1524" layer="21" curve="-90"/>
<wire x1="2.286" y1="0.762" x2="2.286" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="2.032" y1="-1.016" x2="2.286" y2="-0.762" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.286" y1="0.762" x2="-2.032" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.286" y1="-0.762" x2="-2.032" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.032" y1="-1.016" x2="2.032" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="0.762" x2="-2.286" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="1.016" x2="2.032" y2="1.016" width="0.1524" layer="21"/>
<pad name="C" x="-3.81" y="0" drill="0.8128" shape="long"/>
<pad name="A" x="3.81" y="0" drill="0.8128" shape="long"/>
<text x="-2.286" y="1.27" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.286" y="-2.667" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-1.905" y1="-1.016" x2="-1.397" y2="1.016" layer="21"/>
<rectangle x1="2.286" y1="-0.254" x2="2.921" y2="0.254" layer="21"/>
<rectangle x1="-2.921" y1="-0.254" x2="-2.286" y2="0.254" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="D">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.3114" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<text x="-2.54" y="0" size="0.4064" layer="99" align="center">SpiceOrder 1</text>
<text x="2.54" y="0" size="0.4064" layer="99" align="center">SpiceOrder 2</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="1N4148" prefix="D">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
high speed (Philips)</description>
<gates>
<gate name="G$1" symbol="D" x="0" y="0"/>
</gates>
<devices>
<device name="DO35-10" package="DO35-10">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="DO35-7" package="DO35-7">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="wirepad">
<description>&lt;b&gt;Single Pads&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="1,6/0,8">
<description>&lt;b&gt;THROUGH-HOLE PAD&lt;/b&gt;</description>
<wire x1="-0.762" y1="0.762" x2="-0.508" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="0.762" x2="-0.762" y2="0.508" width="0.1524" layer="21"/>
<wire x1="0.762" y1="0.762" x2="0.762" y2="0.508" width="0.1524" layer="21"/>
<wire x1="0.762" y1="0.762" x2="0.508" y2="0.762" width="0.1524" layer="21"/>
<wire x1="0.762" y1="-0.508" x2="0.762" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="0.762" y1="-0.762" x2="0.508" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="-0.762" x2="-0.762" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="-0.762" x2="-0.762" y2="-0.508" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="0.635" width="0.1524" layer="51"/>
<pad name="1" x="0" y="0" drill="0.8128" diameter="1.6002" shape="octagon"/>
<text x="-0.762" y="1.016" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="0" y="0.6" size="0.0254" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="PAD">
<wire x1="-1.016" y1="1.016" x2="1.016" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-1.016" y1="-1.016" x2="1.016" y2="1.016" width="0.254" layer="94"/>
<text x="-1.143" y="1.8542" size="1.778" layer="95">&gt;NAME</text>
<text x="-1.143" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="P" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="1,6/0,8" prefix="PAD" uservalue="yes">
<description>&lt;b&gt;THROUGH-HOLE PAD&lt;/b&gt;</description>
<gates>
<gate name="P" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1,6/0,8">
<connects>
<connect gate="P" pin="P" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="SW1" library="cherrymx" deviceset="CHERRY-MX" device=""/>
<part name="SW2" library="cherrymx" deviceset="CHERRY-MX" device=""/>
<part name="SW3" library="cherrymx" deviceset="CHERRY-MX" device=""/>
<part name="SW4" library="cherrymx" deviceset="CHERRY-MX" device=""/>
<part name="SW5" library="cherrymx" deviceset="CHERRY-MX" device=""/>
<part name="D1" library="diode" deviceset="1N4148" device="DO35-7"/>
<part name="D2" library="diode" deviceset="1N4148" device="DO35-7"/>
<part name="D3" library="diode" deviceset="1N4148" device="DO35-7"/>
<part name="D4" library="diode" deviceset="1N4148" device="DO35-7"/>
<part name="D5" library="diode" deviceset="1N4148" device="DO35-7"/>
<part name="XOUT" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YIN1" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YIN2" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YIN3" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YIN4" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YIN5" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YOUT1" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YOUT2" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YOUT3" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YOUT4" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="YOUT5" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="XIN1" library="wirepad" deviceset="1,6/0,8" device=""/>
<part name="XTRA1" library="wirepad" deviceset="1,6/0,8" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="SW1" gate="G$1" x="35.56" y="106.68"/>
<instance part="SW2" gate="G$1" x="35.56" y="88.9"/>
<instance part="SW3" gate="G$1" x="35.56" y="71.12"/>
<instance part="SW4" gate="G$1" x="35.56" y="53.34"/>
<instance part="SW5" gate="G$1" x="35.56" y="35.56"/>
<instance part="D1" gate="G$1" x="7.62" y="104.14"/>
<instance part="D2" gate="G$1" x="7.62" y="86.36"/>
<instance part="D3" gate="G$1" x="7.62" y="68.58"/>
<instance part="D4" gate="G$1" x="7.62" y="50.8"/>
<instance part="D5" gate="G$1" x="7.62" y="33.02"/>
<instance part="XOUT" gate="P" x="-12.7" y="119.38"/>
<instance part="YIN1" gate="P" x="-2.54" y="104.14"/>
<instance part="YIN2" gate="P" x="-2.54" y="86.36"/>
<instance part="YIN3" gate="P" x="-2.54" y="68.58"/>
<instance part="YIN4" gate="P" x="-2.54" y="50.8"/>
<instance part="YIN5" gate="P" x="-2.54" y="33.02"/>
<instance part="YOUT1" gate="P" x="-2.54" y="101.6"/>
<instance part="YOUT2" gate="P" x="-2.54" y="83.82"/>
<instance part="YOUT3" gate="P" x="-2.54" y="66.04"/>
<instance part="YOUT4" gate="P" x="-2.54" y="48.26"/>
<instance part="YOUT5" gate="P" x="-2.54" y="30.48"/>
<instance part="XIN1" gate="P" x="-15.24" y="25.4"/>
<instance part="XTRA1" gate="P" x="-2.54" y="93.98"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$6" class="0">
<segment>
<pinref part="D1" gate="G$1" pin="A"/>
<pinref part="YIN1" gate="P" pin="P"/>
<wire x1="5.08" y1="104.14" x2="2.54" y2="104.14" width="0.1524" layer="91"/>
<wire x1="2.54" y1="104.14" x2="0" y2="104.14" width="0.1524" layer="91"/>
<wire x1="2.54" y1="104.14" x2="2.54" y2="101.6" width="0.1524" layer="91"/>
<junction x="2.54" y="104.14"/>
<pinref part="YOUT1" gate="P" pin="P"/>
<wire x1="2.54" y1="101.6" x2="0" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="D2" gate="G$1" pin="A"/>
<pinref part="YIN2" gate="P" pin="P"/>
<wire x1="5.08" y1="86.36" x2="2.54" y2="86.36" width="0.1524" layer="91"/>
<wire x1="2.54" y1="86.36" x2="0" y2="86.36" width="0.1524" layer="91"/>
<wire x1="2.54" y1="86.36" x2="2.54" y2="83.82" width="0.1524" layer="91"/>
<junction x="2.54" y="86.36"/>
<pinref part="YOUT2" gate="P" pin="P"/>
<wire x1="2.54" y1="83.82" x2="0" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="D4" gate="G$1" pin="A"/>
<pinref part="YIN4" gate="P" pin="P"/>
<wire x1="5.08" y1="50.8" x2="2.54" y2="50.8" width="0.1524" layer="91"/>
<wire x1="2.54" y1="50.8" x2="0" y2="50.8" width="0.1524" layer="91"/>
<wire x1="2.54" y1="50.8" x2="2.54" y2="48.26" width="0.1524" layer="91"/>
<junction x="2.54" y="50.8"/>
<pinref part="YOUT4" gate="P" pin="P"/>
<wire x1="2.54" y1="48.26" x2="0" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="D5" gate="G$1" pin="A"/>
<pinref part="YIN5" gate="P" pin="P"/>
<wire x1="5.08" y1="33.02" x2="2.54" y2="33.02" width="0.1524" layer="91"/>
<wire x1="2.54" y1="33.02" x2="0" y2="33.02" width="0.1524" layer="91"/>
<wire x1="2.54" y1="33.02" x2="2.54" y2="30.48" width="0.1524" layer="91"/>
<junction x="2.54" y="33.02"/>
<pinref part="YOUT5" gate="P" pin="P"/>
<wire x1="2.54" y1="30.48" x2="0" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="XOUT" class="0">
<segment>
<pinref part="XOUT" gate="P" pin="P"/>
<wire x1="-7.62" y1="38.1" x2="-7.62" y2="55.88" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="55.88" x2="-7.62" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="73.66" x2="-7.62" y2="91.44" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="91.44" x2="-7.62" y2="109.22" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="109.22" x2="-7.62" y2="119.38" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="119.38" x2="-10.16" y2="119.38" width="0.1524" layer="91"/>
<pinref part="SW1" gate="G$1" pin="PIN-1"/>
<wire x1="25.4" y1="109.22" x2="-7.62" y2="109.22" width="0.1524" layer="91"/>
<junction x="-7.62" y="109.22"/>
<pinref part="SW2" gate="G$1" pin="PIN-1"/>
<wire x1="25.4" y1="91.44" x2="-7.62" y2="91.44" width="0.1524" layer="91"/>
<junction x="-7.62" y="91.44"/>
<pinref part="SW3" gate="G$1" pin="PIN-1"/>
<wire x1="25.4" y1="73.66" x2="-7.62" y2="73.66" width="0.1524" layer="91"/>
<junction x="-7.62" y="73.66"/>
<pinref part="SW4" gate="G$1" pin="PIN-1"/>
<wire x1="25.4" y1="55.88" x2="-7.62" y2="55.88" width="0.1524" layer="91"/>
<junction x="-7.62" y="55.88"/>
<pinref part="SW5" gate="G$1" pin="PIN-1"/>
<wire x1="25.4" y1="38.1" x2="-7.62" y2="38.1" width="0.1524" layer="91"/>
<pinref part="XIN1" gate="P" pin="P"/>
<wire x1="-12.7" y1="25.4" x2="-7.62" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="25.4" x2="-7.62" y2="38.1" width="0.1524" layer="91"/>
<junction x="-7.62" y="38.1"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="SW1" gate="G$1" pin="PIN-2"/>
<pinref part="D1" gate="G$1" pin="C"/>
<wire x1="25.4" y1="104.14" x2="17.78" y2="104.14" width="0.1524" layer="91"/>
<pinref part="XTRA1" gate="P" pin="P"/>
<wire x1="17.78" y1="104.14" x2="10.16" y2="104.14" width="0.1524" layer="91"/>
<wire x1="0" y1="93.98" x2="17.78" y2="93.98" width="0.1524" layer="91"/>
<wire x1="17.78" y1="93.98" x2="17.78" y2="104.14" width="0.1524" layer="91"/>
<junction x="17.78" y="104.14"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="YIN3" gate="P" pin="P"/>
<pinref part="D3" gate="G$1" pin="A"/>
<wire x1="0" y1="68.58" x2="2.54" y2="68.58" width="0.1524" layer="91"/>
<pinref part="YOUT3" gate="P" pin="P"/>
<wire x1="2.54" y1="68.58" x2="5.08" y2="68.58" width="0.1524" layer="91"/>
<wire x1="0" y1="66.04" x2="2.54" y2="66.04" width="0.1524" layer="91"/>
<wire x1="2.54" y1="66.04" x2="2.54" y2="68.58" width="0.1524" layer="91"/>
<junction x="2.54" y="68.58"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="D5" gate="G$1" pin="C"/>
<pinref part="SW5" gate="G$1" pin="PIN-2"/>
<wire x1="10.16" y1="33.02" x2="25.4" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="D4" gate="G$1" pin="C"/>
<pinref part="SW4" gate="G$1" pin="PIN-2"/>
<wire x1="10.16" y1="50.8" x2="25.4" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="D3" gate="G$1" pin="C"/>
<pinref part="SW3" gate="G$1" pin="PIN-2"/>
<wire x1="10.16" y1="68.58" x2="25.4" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="D2" gate="G$1" pin="C"/>
<pinref part="SW2" gate="G$1" pin="PIN-2"/>
<wire x1="10.16" y1="86.36" x2="25.4" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
