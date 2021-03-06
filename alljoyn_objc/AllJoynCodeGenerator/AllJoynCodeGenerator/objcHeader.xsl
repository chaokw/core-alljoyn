<!--
////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for any
//    purpose with or without fee is hereby granted, provided that the above
//    copyright notice and this permission notice appear in all copies.
//
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////
-->
<xsl:stylesheet version="1.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="fileName"/>

<xsl:output method="text" version="1.0" encoding="UTF-8" indent="no" omit-xml-declaration="yes"/>

<xsl:variable name="vLower" select="'abcdefghijklmnopqrstuvwxyz'"/>
<xsl:variable name="vUpper" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ'"/>

<xsl:template match="/">
<xsl:text>////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for any
//    purpose with or without fee is hereby granted, provided that the above
//    copyright notice and this permission notice appear in all copies.
//
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//  ALLJOYN MODELING TOOL - GENERATED CODE
//
////////////////////////////////////////////////////////////////////////////////
//
//  DO NOT EDIT
//
//  Add a category or subclass in separate .h/.m files to extend these classes
//
////////////////////////////////////////////////////////////////////////////////
//
//  </xsl:text><xsl:value-of select="$fileName"/><xsl:text>
//
////////////////////////////////////////////////////////////////////////////////

#import &lt;Foundation&#47;Foundation.h&gt;
#import "AJNBusAttachment.h"
#import "AJNBusInterface.h"
#import "AJNProxyBusObject.h"
</xsl:text>

<xsl:apply-templates select=".//interface"/>
<xsl:apply-templates select=".//node"/>

</xsl:template>

<xsl:template match="interface">

////////////////////////////////////////////////////////////////////////////////
//
// <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/> Bus Interface
//
////////////////////////////////////////////////////////////////////////////////

@protocol <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/> &lt;AJNBusInterface&gt;

<xsl:if test="count(./property)>0">
// properties
//
<xsl:apply-templates select="./property" mode="objc-declaration"/>
</xsl:if>
<xsl:if test="count(./method)>0">
// methods
//
<xsl:apply-templates select="./method" mode="objc-declaration"/>
</xsl:if>
<xsl:if test="count(./signal)>0">
// signals
//
<xsl:apply-templates select="./signal" mode="objc-declaration"/>
</xsl:if>

@end

////////////////////////////////////////////////////////////////////////////////

    <xsl:if test="count(./signal)>0">
////////////////////////////////////////////////////////////////////////////////
//
// <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/> Signal Handler Protocol
//
////////////////////////////////////////////////////////////////////////////////

@protocol <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/>SignalHandler &lt;AJNSignalHandler&gt;

// signals
//
<xsl:apply-templates select="./signal" mode="objc-signal-handler-declaration"/>

@end

@interface AJNBusAttachment(<xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/>)

- (void)register<xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/>SignalHandler:(id&lt;<xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/>SignalHandler&gt;)signalHandler;

@end

////////////////////////////////////////////////////////////////////////////////
    </xsl:if>
</xsl:template>


<xsl:template match="node">

////////////////////////////////////////////////////////////////////////////////
//
//  AJN<xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/> Bus Object superclass
//
////////////////////////////////////////////////////////////////////////////////

@interface AJN<xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value" /> : AJNBusObject&lt;<xsl:apply-templates select="./interface" mode="objc-interface-list"/>&gt;

// properties
//
<xsl:apply-templates select="./interface/property" mode="objc-declaration"/>

// methods
//
<xsl:apply-templates select="./interface/method" mode="objc-declaration"/>

// signals
//
<xsl:apply-templates select="./interface/signal" mode="objc-declaration"/>

@end

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/> Proxy
//
////////////////////////////////////////////////////////////////////////////////

@interface <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value" />Proxy : AJNProxyBusObject

// properties
//
<xsl:apply-templates select=".//property" mode="objc-declaration"/>

// methods
//
<xsl:apply-templates select=".//method" mode="objc-declaration-proxy"/>

@end

////////////////////////////////////////////////////////////////////////////////
</xsl:template>

<xsl:template match="interface" mode="objc-interface-list">
    <xsl:if test="position() > 1">, </xsl:if>
    <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value"/>
</xsl:template>

<xsl:template match="method" mode="objc-declaration">
    <xsl:text>- (</xsl:text>
    <xsl:choose>
        <xsl:when test="count(./arg[@direction='out']) > 1 or count(./arg[@direction='out']) = 0">
            <xsl:text>void</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:apply-templates select="./arg[@direction='out']" mode="objc-argType"/>
        </xsl:otherwise>
    </xsl:choose>
    <xsl:text>)</xsl:text>
    <xsl:choose>
        <xsl:when test="count(./arg) = 0 or (count(./arg) = 1 and count(./arg[@direction='out']) = 1)">
            <xsl:call-template name="uncapitalizeFirstLetterOfNameAttr"/>
            <xsl:text>:(AJNMessage *)methodCallMessage</xsl:text>
        </xsl:when>
        <xsl:when test="count(./arg[@direction='out']) > 1">
            <xsl:apply-templates select="./arg[@direction='in']" mode="objc-messageParam"/>
            <xsl:if test="count(./arg[@direction='in']) > 1">
                <xsl:text>&#32;</xsl:text>
            </xsl:if>
            <xsl:apply-templates select="./arg[@direction='out']" mode="objc-messageParam"/>
            <xsl:text> message:(AJNMessage *)methodCallMessage</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:apply-templates select="./arg[@direction='in']" mode="objc-messageParam"/>
            <xsl:text> message:(AJNMessage *)methodCallMessage</xsl:text>
        </xsl:otherwise>
    </xsl:choose>
    <xsl:text>;&#10;</xsl:text>
</xsl:template>

<xsl:template match="method" mode="objc-declaration-proxy">
    <xsl:text>- (</xsl:text>
    <xsl:choose>
        <xsl:when test="count(./arg[@direction='out']) > 1 or count(./arg[@direction='out']) = 0">
            <xsl:text>void</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:apply-templates select="./arg[@direction='out']" mode="objc-argType"/>
        </xsl:otherwise>
    </xsl:choose>
    <xsl:text>)</xsl:text>
    <xsl:choose>
        <xsl:when test="count(./arg) = 0 or (count(./arg) = 1 and count(./arg[@direction='out']) = 1)">
            <xsl:call-template name="uncapitalizeFirstLetterOfNameAttr"/>
        </xsl:when>
        <xsl:when test="count(./arg[@direction='out']) > 1">
            <xsl:apply-templates select="./arg[@direction='in']" mode="objc-messageParam"/>
            <xsl:if test="count(./arg[@direction='in']) > 1">
                <xsl:text>&#32;</xsl:text>
            </xsl:if>
            <xsl:apply-templates select="./arg[@direction='out']" mode="objc-messageParam"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:apply-templates select="./arg[@direction='in']" mode="objc-messageParam"/>
        </xsl:otherwise>
    </xsl:choose>
    <xsl:text>;&#10;</xsl:text>
</xsl:template>

<xsl:template match="signal" mode="objc-declaration">
    <xsl:text>- (void)send</xsl:text>
    <xsl:choose>
        <xsl:when test="count(./arg) > 0">
            <xsl:apply-templates select="./arg" mode="objc-messageParam"/>
            <xsl:text> inSession:(AJNSessionId)sessionId</xsl:text>            
        </xsl:when>
        <xsl:when test="count(./arg) = 0">
            <xsl:value-of select="@name"/>        
            <xsl:text>InSession:(AJNSessionId)sessionId</xsl:text>            
        </xsl:when>
    </xsl:choose>    
    <xsl:text> toDestination:(NSString*)destinationPath;&#10;</xsl:text>
</xsl:template>

<xsl:template match="signal" mode="objc-signal-handler-declaration">
    <xsl:text>- (void)didReceive</xsl:text>
    <xsl:choose>
        <xsl:when test="count(./arg) > 0">
            <xsl:apply-templates select="./arg" mode="objc-messageParam"/>
            <xsl:text> inSession:(AJNSessionId)sessionId</xsl:text>            
        </xsl:when>
        <xsl:when test="count(./arg) = 0">
            <xsl:value-of select="@name"/>        
            <xsl:text>InSession:(AJNSessionId)sessionId</xsl:text>            
        </xsl:when>
    </xsl:choose>    
    <xsl:text> message:(AJNMessage *)signalMessage;&#10;</xsl:text>
</xsl:template>

<xsl:template match="property" mode="objc-declaration">
    <xsl:text>@property (nonatomic,</xsl:text>
    <xsl:choose>
        <xsl:when test="@access='readwrite'">
            <xsl:if test="@type!='b'">
                <xsl:text> strong</xsl:text>
            </xsl:if>
        </xsl:when>
        <xsl:when test="@access='read'">
            <xsl:text> readonly</xsl:text>
        </xsl:when>
    </xsl:choose>
    <xsl:text>) </xsl:text>
    <xsl:call-template name="objcArgType"/>
    <xsl:text> </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>;&#10;</xsl:text>
</xsl:template>

<xsl:template match="arg" mode="objc-messageParam">
    <xsl:if test="position() > 1">
        <xsl:text>&#32;</xsl:text>
    </xsl:if>
    <xsl:value-of select="./annotation[@name='org.alljoyn.lang.objc']/@value" />
    <xsl:text>(</xsl:text>
        <xsl:apply-templates select="." mode="objc-argType"/>
        <xsl:if test="@direction='out'">
            <xsl:text>*</xsl:text>
        </xsl:if>
    <xsl:text>)</xsl:text>
    <xsl:value-of select="@name"/>
</xsl:template>

<xsl:template match="arg" mode="objc-argType">
    <xsl:call-template name="objcArgType"/>
</xsl:template>

<xsl:template name="objcArgType">
    <xsl:choose>
        <xsl:when test="@type='y'">
            <xsl:text>NSNumber*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='b'">
            <xsl:text>BOOL</xsl:text>
        </xsl:when>
        <xsl:when test="@type='n'">
            <xsl:text>NSNumber*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='q'">
            <xsl:text>NSNumber*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='i'">
            <xsl:text>NSNumber*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='u'">
            <xsl:text>NSNumber*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='x'">
            <xsl:text>NSNumber*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='t'">
            <xsl:text>NSNumber*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='d'">
            <xsl:text>NSNumber*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='s'">
            <xsl:text>NSString*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='o'">
            <xsl:text>NSString*</xsl:text>
        </xsl:when>
        <xsl:when test="@type='a'">
            <xsl:text>NSArray*</xsl:text>
        </xsl:when>
        <xsl:otherwise>
            <xsl:text>AJNMessageArgument*</xsl:text>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<xsl:template name="capitalizeFirstLetterOfNameAttr">  
   <xsl:variable name="value">  
        <xsl:value-of select="@name"/>  
   </xsl:variable>  
    <xsl:variable name= "ufirstChar" select="translate(substring($value,1,1),$vLower,$vUpper)"/>  
    <xsl:value-of select="concat($ufirstChar,substring($value,2))"/>
</xsl:template>

<xsl:template name="uncapitalizeFirstLetterOfNameAttr">  
   <xsl:variable name="value">  
        <xsl:value-of select="@name"/>  
   </xsl:variable>  
    <xsl:variable name= "lfirstChar" select="translate(substring($value,1,1),$vUpper,$vLower)"/>  
    <xsl:value-of select="concat($lfirstChar,substring($value,2))"/>
</xsl:template>

</xsl:stylesheet>
