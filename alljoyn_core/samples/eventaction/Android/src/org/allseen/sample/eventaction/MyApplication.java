/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/
package org.allseen.sample.eventaction;

import android.app.Application;

public class MyApplication extends Application implements EventActionListener {
	EventActionListener mChainedListener = null;
	 public void onCreate() {
	
	 }
	 
	 public void setChainedListener(EventActionListener listener) {
		 mChainedListener = listener;
	 }
	 
	 @Override
	public void onEventFound(Device info) {
		 if(mChainedListener != null)
			 mChainedListener.onEventFound(info);
	}

	@Override
	public void onActionsFound(Device info) {
		if(mChainedListener != null)
			 mChainedListener.onActionsFound(info);
	}
	
	@Override
	public void onRuleEngineFound(final String sessionName, final String friendlyName) {
		if(mChainedListener != null)
			 mChainedListener.onRuleEngineFound(sessionName, friendlyName);
	}

	@Override
	public void onAppLost(String busName) {
		if(mChainedListener != null)
			 mChainedListener.onAppLost(busName);
	}
	
	@Override
	public void onAppReturned(String busName) {
		if(mChainedListener != null)
			 mChainedListener.onAppReturned(busName);
	}
}
