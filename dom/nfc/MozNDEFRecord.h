/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Copyright © 2013 Deutsche Telekom, Inc. */

#ifndef mozilla_dom_MozNDEFRecord_h__
#define mozilla_dom_MozNDEFRecord_h__

#include "mozilla/Attributes.h"
#include "mozilla/ErrorResult.h"
#include "nsCycleCollectionParticipant.h"
#include "nsWrapperCache.h"
#include "jsapi.h"

#include "nsIDocument.h"

#include "mozilla/dom/TypedArray.h"
#include "jsfriendapi.h"
#include "js/GCAPI.h"

struct JSContext;

namespace mozilla {
namespace dom {

class MozNDEFRecord MOZ_FINAL : public nsISupports,
                                public nsWrapperCache
{
public:
  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS(MozNDEFRecord)

public:

  MozNDEFRecord(JSContext* aCx, nsPIDOMWindow* aWindow, uint8_t aTnf,
                const Optional<Uint8Array>& aType,
                const Optional<Uint8Array>& aId,
                const Optional<Uint8Array>& aPlayload);

  ~MozNDEFRecord();

  nsIDOMWindow* GetParentObject() const
  {
    return mWindow;
  }

  virtual JSObject* WrapObject(JSContext* aCx) MOZ_OVERRIDE;

  static already_AddRefed<MozNDEFRecord>
  Constructor(const GlobalObject& aGlobal, uint8_t aTnf,
              const Optional<Uint8Array>& aType,
              const Optional<Uint8Array>& aId,
              const Optional<Uint8Array>& aPayload, ErrorResult& aRv);

  uint8_t Tnf() const
  {
    return mTnf;
  }

  JSObject* GetType(JSContext* cx) const
  {
    if (mType) {
      return GetTypeObject();
    } else {
      return nullptr;
    }
  }
  JSObject* GetTypeObject() const
  {
    JS::ExposeObjectToActiveJS(mType);
    return mType;
  }

  JSObject* GetId(JSContext* cx) const
  {
    if (mId) {
      return GetIdObject();
    } else {
      return nullptr;
    }
  }
  JSObject* GetIdObject() const
  {
    JS::ExposeObjectToActiveJS(mId);
    return mId;
  }

  JSObject* GetPayload(JSContext* cx) const
  {
    if (mPayload) {
      return GetPayloadObject();
    } else {
      return nullptr;
    }
  }
  JSObject* GetPayloadObject() const
  {
    JS::ExposeObjectToActiveJS(mPayload);
    return mPayload;
  }

private:
  MozNDEFRecord() MOZ_DELETE;
  nsRefPtr<nsPIDOMWindow> mWindow;
  void HoldData();
  void DropData();

  uint8_t mTnf;
  JS::Heap<JSObject*> mType;
  JS::Heap<JSObject*> mId;
  JS::Heap<JSObject*> mPayload;
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_MozNDEFRecord_h__
