/*******************************************************************************
 * Copyright (c) 2000, 2016 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at http://eclipse.org/legal/epl-2.0
 * or the Apache License, Version 2.0 which accompanies this distribution
 * and is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following Secondary
 * Licenses when the conditions for such availability set forth in the
 * Eclipse Public License, v. 2.0 are satisfied: GNU General Public License,
 * version 2 with the GNU Classpath Exception [1] and GNU General Public
 * License, version 2 with the OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0
 *******************************************************************************/

#include <stddef.h>                       // for NULL
#include "codegen/Machine.hpp"            // for Machine
#include "codegen/RealRegister.hpp"       // for RealRegister
#include "codegen/Register.hpp"           // for Register
#include "codegen/RegisterConstants.hpp"  // for TR_RegisterKinds, etc
#include "codegen/RegisterIterator.hpp"   // for RegisterIterator
#include "infra/Assert.hpp"               // for TR_ASSERT

OMR::X86::RegisterIterator::RegisterIterator(TR::Machine *machine, TR_RegisterKinds kind)
   {
   _machine = machine;
   if (kind == TR_GPR)
      {
      _firstRegIndex = TR::RealRegister::eax;
      _lastRegIndex = TR::RealRegister::LastAssignableGPR;
      }
   else if (kind == TR_FPR || kind == TR_VRF)
      {
      _firstRegIndex = TR::RealRegister::xmm0;
      _lastRegIndex = TR::RealRegister::LastXMMR;
      }
   else
      {
      TR_ASSERT(0, "Bad register kind for X86\n");
      }
   _cursor = _firstRegIndex;
   }

TR::Register *
OMR::X86::RegisterIterator::getFirst()
   {
   return _machine->getX86RealRegister((TR::RealRegister::RegNum)(_cursor = _firstRegIndex));
   }

TR::Register *
OMR::X86::RegisterIterator::getCurrent()
   {
   return _machine->getX86RealRegister((TR::RealRegister::RegNum)_cursor);
   }

TR::Register *
OMR::X86::RegisterIterator::getNext()
   {
   return _cursor == _lastRegIndex ? NULL : _machine->getX86RealRegister((TR::RealRegister::RegNum)(++_cursor));
   }
